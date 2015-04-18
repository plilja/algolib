include <iostream>
include <list>
include <vector>
include <math.h>
include "minspantree.h"
include "matching.h"
include "eulerianpath.h"
 
using namespace std;
 
 
bool edge_cmp(const pair<pair<int, int>, int> &i, const pair<pair<int, int>, int> &j)
{
if(i.first.first==j.first.first)
return i.second<j.second;
return i.first.first<j.first.first;
}

 
void reduce(list<pair<pair<int, int>, int> > &edges_reduced, list<pair<pair<int, int>, int> > &edges, const vector<pair<int, int> > &min_max, double limit)
{
 
 
for(list<pair<pair<int, int>, int> >::iterator it=edges.begin();it!=edges.end(); ++it)
{
const pair<int,int> &p=min_max[it->first.first];
if(it->second<=p.first+limit*(p.second-p.first))
edges_reduced.push_back(*it);
}
}

int main()
{
int num_nodes;
scanf("%d", &num_nodes);
if(num_nodes==1)
{
printf("0\n");
return 0;
}
double a, b;
int dist;
list<pair<pair<int, int>, int> > edges;
vector<pair<double,double> > points;
vector<pair<int, int> > min_max;
for(int i=0; i<num_nodes; ++i)
{
scanf("%lf %lf", &a, &b);
points.push_back(make_pair(a, b));
}
for(int i=0; i<num_nodes; ++i)
{
int min_dist=std::numeric_limits<int>::max();
int max_dist=0;
for(int j=i+1; j<num_nodes; ++j)
{
dist=(int)sqrt(pow(points[i].first-points[j].first, 2)+
pow(points[i].second-points[j].second, 2));
min_dist=min(min_dist, dist);
max_dist=max(max_dist, dist);
edges.push_back(make_pair(make_pair(i, j), dist));
}
min_max.push_back(make_pair(min_dist, max_dist));
}
list<pair<pair<int, int>, int> > edges_reduced;
 
double limit=1.1-0.001*num_nodes;
reduce(edges_reduced, edges, min_max, limit);
//edges.sort(edge_cmp);
//for(list<pair<pair<int, int>, int> >::iterator it=edges.begin();
//it!=edges.end(); ++it)
//cout<<it->first.first<<" "<<it->first.second<<" : "<<it->second<<endl;
 
list<pair<pair<int, int>, int> > mst;
prim(mst, num_nodes, edges_reduced);
 
list<pair<pair<int, int>, int> > matching;
 
greedy_matching(num_nodes, mst, edges, matching);
 
/*cout<<"REDUCED: "<<endl;
  for(list<pair<pair<int, int>, int> >::iterator it=edges_reduced.begin();
  it!=edges_reduced.end(); ++it)
  cout<<it->first.first<<" "<<it->first.second<<" : "<<it->second<<endl;
 
  edges.sort(edge_cmp);
  cout<<"MST: "<<endl;
  for(list<pair<pair<int, int>, int> >::iterator it=mst.begin();
  it!=mst.end(); ++it)
  cout<<it->first.first<<" "<<it->first.second<<" : "<<it->second<<endl;
 
  matching.sort(edge_cmp);
  cout<<endl<<"MATCHING: "<<endl;
  for(list<pair<pair<int, int>, int> >::iterator it=matching.begin();
  it!=matching.end(); ++it)
  cout<<it->first.first<<" "<<it->first.second<<" : "<<it->second<<endl;*/
 
mst.insert(mst.end(), matching.begin(), matching.end());
list<int> tsp_path;
eulerpath(tsp_path, mst, num_nodes);
for(list<int>::iterator it=tsp_path.begin();it!=tsp_path.end(); ++it)
printf("%d\n", *it);

//for(int i=0; i<num_nodes; ++i)

//printf("%d\n", i);

}
