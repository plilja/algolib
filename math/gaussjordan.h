#pragma once

#include <vector>
#include <list>
#include <cmath>

typedef unsigned int uint;

enum GaussJordanResult {
    SUCCESS, INCONSISTENT, MULTIPLE, MATRIX_NOT_ZERO
};

template <typename T>
bool isZero(T v)
{
    return v==0;
}

template <>
bool isZero<long double>(long double v)
{
    long double absv = v < 0 ? -v : v;
    return absv < 0.00000000001;
}

template <>
bool isZero<double>(double v)
{
    return fabs(v) < 0.00000001;
}

template <>
bool isZero<float>(float v)
{
    return fabs(v) < 0.0000001;
}


template <typename T>
GaussJordanResult isZeroSystem(const std::vector<std::vector<T> > &A, const std::vector<T> &y)
{
    uint dim=A.size();
    for(uint i=0; i<dim; ++i) {
        for(uint j=0; j<dim; ++j) {
            if(!isZero(A[i][j])) {
                return MATRIX_NOT_ZERO;
            }
        }
    }
    for(uint i=0; i<dim; ++i) {
        if(!isZero(y[i])) {
            return INCONSISTENT;
        }
    }
    return MULTIPLE;
}

template <typename T>
int findPivot(uint column, uint next_row, const std::vector<std::vector<T>* > &A)
{
    uint dim=A.size();
    for(uint j=next_row; j<dim; ++j) {
        if(!isZero((*A[j])[column])) {
            return j;
        }
    }
    return -1;

}

template <typename T>
GaussJordanResult gaussjordan(std::vector<std::vector<T> > A, std::vector<T> y, std::vector<T> &x)
{
    auto c = isZeroSystem(A, y);
    if(c == INCONSISTENT) {
        return INCONSISTENT;
    }
    else if(c == MULTIPLE) {
        return MULTIPLE;
    }

    uint dim = A.size();
    
    //copy A to vector<vector*> for ability to
    //swap rows quickly
    std::vector<std::vector<T>* > _A(A.size());
    for(uint i = 0; i < A.size(); ++i) {
        _A[i]=&A[i];
    }
    
    uint next_row = 0;
    int pivot_pos;
    bool linear_independent_lines=true;
    for(uint i = 0; i < dim; ++i) {
        pivot_pos=findPivot(i, next_row, _A);
        if(pivot_pos == -1) {
            linear_independent_lines=false;
            continue;
        }
        std::swap(_A[next_row], _A[pivot_pos]);
        std::swap(y[next_row], y[pivot_pos]);

        T pivot=(*_A[next_row])[i];
        for(uint j = next_row + 1; j < dim; ++j) {
            if(j==next_row) {
                continue;
            }
            T factor=(*_A[j])[i]/pivot;
            (*_A[j])[i]=0;
            y[j] -= y[next_row]*factor;
            
            bool line_is_zero= true;
            for(uint z = i+1; z < dim; ++z)
            {
                (*_A[j])[z] -= (*_A[next_row])[z] * factor;
                line_is_zero = line_is_zero && isZero((*_A[j])[z]); 
            }
            if(line_is_zero)
            {
                linear_independent_lines=false;
                if(!isZero(y[j]))
                {
                    return INCONSISTENT;
                }
            }
        }
        next_row++;
    }

    if(!linear_independent_lines) {
        return MULTIPLE;
    }
    
    x = std::vector<T>(dim, T());
    for(uint i = 0; i < dim; ++i) {
        x[i]=y[i];
    }
    
    for(int i=dim-1; i>=0; --i) {
        T A_i_i=(*_A[i])[i];
        for(int j=i-1; j>=0; --j) {
            x[j] -= x[i]*(*_A[j])[i]/A_i_i;
        }
    }
    for(uint i=0; i<dim; ++i) {
        x[i]=x[i]/(*_A[i])[i];
    }
    
    return SUCCESS;
}

template <typename T>
GaussJordanResult gaussjordanplus(std::vector<std::vector<T> > A, std::vector<T> y, std::vector<std::pair<bool,T> > &x)
{
    uint dim = A.size();
    auto c = isZeroSystem(A, y);
    if(c == INCONSISTENT) {
        return INCONSISTENT;
    }
    else if(c == MULTIPLE)
    {
        x = std::vector<std::pair<bool, T> >(dim, std::pair<bool, T>(false, T()));
        return MULTIPLE;
    }
    
    //copy A to vector<vector*> for ability to
    //swap rows quickly
    std::vector<std::vector<T>* > _A(A.size());
    for(uint i = 0; i < A.size(); ++i)
        _A[i] = &A[i];
    
    uint next_row = 0;
    int pivot_pos;
    bool linear_independent_lines = true;
    for(uint i = 0; i < dim; ++i) {
        pivot_pos = findPivot(i, next_row, _A);
        if(pivot_pos == -1)
        {
            linear_independent_lines = false;
            continue;
        }
        std::swap(_A[next_row], _A[pivot_pos]);
        std::swap(y[next_row], y[pivot_pos]);
        T pivot = (*_A[next_row])[i];
        for(uint j = next_row + 1; j < dim; ++j)
        {
            if(j == next_row) {
                continue;
            }
            T factor = (*_A[j])[i]/pivot;
            (*_A[j])[i] = 0;
            y[j] -= y[next_row] * factor;
            
            bool line_is_zero = true;
            for(uint z = i + 1; z <  dim; ++z)
            {
                (*_A[j])[z] -= (*_A[next_row])[z] * factor;
                line_is_zero = line_is_zero && isZero((*_A[j])[z]); 
            }
            if(line_is_zero)
            {
                linear_independent_lines = false;
                if(!isZero(y[j]))
                {
                    return INCONSISTENT;
                }
            }
        }
        next_row++;
    }

    x = std::vector<std::pair<bool, T> >(dim, std::pair<bool, T>(false, T()));
    if(!linear_independent_lines) {
        uint next_col = dim - 1;
        for(int i = dim - 1; i > 0; --i) {
            bool zero_line = true;
            for(int j = dim - 1; j >= 0; --j) {
                if(!isZero((*_A[i])[j])) {
                    zero_line = false;
                    next_col = j;
                    break;
                }
            }
            if(zero_line) {
                continue;
            }
            T pivot = (*_A[i])[next_col];
            for(int j = i-1; j >= 0; --j) {
                T factor=(*_A[j])[next_col] / pivot;
                (*_A[j])[next_col] = 0;
                y[j] -= y[i] * factor;
                for(int z = next_col - 1; z >= 0; --z) {
                    (*_A[j])[z] -= (*_A[i])[z]*factor;
                }
            }
        }
        for(uint i = 0; i < dim; ++i) {
            x[i] = std::make_pair(false,0);
        }
        for(uint i = 0; i < dim; ++i) {
            uint nr_of_not_zeros = 0;
            uint pos = 0;
            for(uint j = 0; j < dim; ++j) {
                bool is_not_zero = !isZero((*_A[i])[j]);
                nr_of_not_zeros += is_not_zero;
                if(is_not_zero) {
                    pos = j;
                }
            }
            if(nr_of_not_zeros == 1) {
                x[pos] = std::make_pair(true, y[i]/(*_A[i])[pos]);
            }
        }
        return MULTIPLE;
    }
    
    for(uint i = 0; i < dim; ++i) {
        x[i] = std::make_pair(true, y[i]);
    }
    
    for(int i = dim-1; i >= 0; --i) {
        T A_i_i = (*_A[i])[i];
        for(int j = i - 1; j >= 0; --j) {
            x[j].second -= x[i].second*(*_A[j])[i] / A_i_i;
        }
    }
    for(uint i = 0; i < dim; ++i) {
        x[i].second = x[i].second / (*_A[i])[i];
    }
        
    return SUCCESS;
}

