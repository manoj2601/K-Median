#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "allclasses.h"
#define MAX_SIZE INT_MAX
using namespace std;


int Luvt(int t, Node* v, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges);



Node* find_mv(Node* current_node)
{
    if((current_node->node_child).size() == 0){
        return current_node;
    }
    
    return find_mv((current_node->node_child)[0]);
}
int search_edge(Node* x, Node* u, vector<Edge*> edge_vector){//search whether an edge is present or not.

    int size = edge_vector.size();
    Edge* obj;
    if(size ==0)
    return -1;
    for(int i=0; i<size; i++){
        obj = edge_vector[i];
        Node* a = obj->firstNode;
        Node* b = obj->secondNode;
        if(a==x && b==u)
        return obj->length;
    }
    return -1;
}
void L1(Node* root, vector<ObjectL1*> &vec, int &node_number)    //array is passed by reference.
{
    //base case1: when the only node is root

    // cout<<"into the loop\n";
    // cout<<"node_number"<<node_number<<endl;
    if((root->node_child).size() == 0 &&  (root->parent) == nullptr){
        // cout<<"only root\n";
        ObjectL1* obj ;
        if(node_number == 0)
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number+1);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);

        node_number += 1;
        vec.push_back(obj);
        return;
    }

    //base case2: when the node is the leaf node.
    if((root->node_child).size() == 0){
        //cout<<"leaf node\n";
        ObjectL1* obj;

        if(node_number == 0)
        obj = new ObjectL1(root, find_mv(root), nullptr, node_number+1);
        else
        obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);
        
        node_number += 1;
        vec.push_back(obj);
        return;
    }

    //recursive program.
    int size = (root->node_child).size();
    for(int i=0; i< size; i++){
        L1((root->node_child)[i], vec, node_number);
    }
    ObjectL1* obj = new ObjectL1(root, find_mv(root), (vec[node_number-1])->node, node_number+1);
    node_number += 1;
    vec.push_back(obj);
    return;
}

int distance(Node* x, Node* u, vector<Edge*> edge_vector){

    Node* child = x;
    Node* parent = child->parent;
    int dist = 0;
    int  y=0;
    if(x==u){
        return 0;
    }
    while(parent!=u ){
        y = search_edge(child, parent, edge_vector);
        dist += y;
        child = parent;
        parent = child->parent;
    }

    y = search_edge(child, parent, edge_vector);
    dist += y;
    return dist;
    

}

int T_uv_Zero(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edge_vector)
{
    Node* Mv = find_mv(v);
    int i = Mv->post_order_number;
    int j = v->post_order_number;
    int ans = 0;

    for(int k=i; k<=j; k++){
        int wt = nodesFinal[k-1]->node->weight;
        ans += wt * distance(nodesFinal[k-1]->node, u, edge_vector);
    }
    return ans;

}

int Tv1(Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges) 
{
    Node* Mv = find_mv(v);
	int mv = Mv->post_order_number;
    int j = v->post_order_number;
    int d = 0;
    for(int i = mv; i <= j; i++)
    {
        d += distance(nodesFinal[i-1]->node, v, edges) * nodesFinal[i-1]->node->weight;      //add distance of child to parent
    }

	return d;
}

int Ruv1(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)   //u: parent node;, v: child node
{
    int ans=0;
    int i = u->post_order_number;
    int j = v->post_order_number;

    for(int k=j+1;k<i;k++)
    {
        int w=nodesFinal[k-1]->node->weight;
        ans+=w * distance(nodesFinal[k-1]->node, u, edges);
    }
    return ans;
}

int Luv0(Node* u, Node* v, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{
    int ans=0;
    int i = v->post_order_number;
    int j = u->post_order_number;
    int mv=((nodesFinal[i-1])->mv)->post_order_number;
    int mu=((nodesFinal[j-1])->mv)->post_order_number;
    for(int k=mu; k<mv; k++)
    {
        int w=nodesFinal[k-1]->node->weight;
        ans+=w * distance(nodesFinal[k-1]->node, nodesFinal[j-1]->node, edges);
    }
    return ans;
}

int minimum(int a, int b){
    if(a<b)
    return a;
    else b;
}
int maximum(int a, int b){
    if(a<b)
    return b;
    return a;
}

int tree_size(int u, vector<ObjectL1* > vec)
{
    
    int mu = (vec[u-1])->mv->post_order_number;
    return u-mu+1;
}

int LuvSize(int u, int v, vector<ObjectL1*> nodesFinal){
    int mv = nodesFinal[v-1]->mv->post_order_number;
    int mu = nodesFinal[u-1]->mv->post_order_number;
    return mv-mu;
}


int T_u_t(int t, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges)
{   
// cout<<"t: "<<t<<endl;
    if(t>= (u->post_order_number - find_mv(u)->post_order_number + 1))
    return 0;
    //base case.
    if(t == 1){
        int x = Tv1(u, nodesFinal, edges);
        return x;
    }

    //recursive
    int mu = find_mv(u)->post_order_number;
    int j = u->post_order_number;
    int y=MAX_SIZE;
    for(int i=mu; i<j; i++)
    {

        int x=MAX_SIZE;
        
        for(int l = maximum(1, t-1-LuvSize(j, i, nodesFinal)); l<minimum(t, tree_size(i,nodesFinal)); l++){
            // cout<<"l: "<<l<<endl;
            int a = T_u_t(l, (nodesFinal[i-1])->node, nodesFinal, edges);
            // cout<<"a: "<<a<<"  "<<"t-l-1: "<<t-l-1<<endl;
            a = a + Luvt(t-l-1, (nodesFinal[i-1])->node, u, nodesFinal, edges);
            // cout<<"a after Luvt: "<<a<<endl;
            a = a + Ruv1(u, (nodesFinal[i-1])->node, nodesFinal, edges);
            // cout<<"a after Ruv1: "<<a<<endl;
            if(a<x) x=a;


        }
        if(x<y)
        y=x;
    }

    return y;
}

int Luvt(int t, Node* v, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){
    //negative case
    if(t<0)
    return 0;

    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v, nodesFinal, edges);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int net_min =MAX_SIZE;
    for(int x=mu; x<mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x, nodesFinal)); i<minimum(t, tree_size(x, nodesFinal)); i++){
            Node* ex = nodesFinal[x-1]->node;
            int a = T_u_t(i, ex, nodesFinal, edges);
            a = a + Luvt(t-i, ex, u, nodesFinal, edges);
            a = a + Ruv1(u, ex, nodesFinal, edges);
            a = a - Ruv1(u, v, nodesFinal, edges);
            a = a - T_uv_Zero(u, v, nodesFinal, edges);

            if(a<min)   min= a;
        }
        if(min<net_min) net_min = min;
    }
    // cout<<"happy"<<endl;
    if(net_min != MAX_SIZE)
    return net_min;
    // cout<<"see"<<endl;
    return 0;
}

int A_uvt(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){

    int post_v = v->post_order_number;
    int a = Luvt(t, nodesFinal[post_v -1]->mv_prime, u, nodesFinal, edges);
    a = a + Ruv1(u, nodesFinal[post_v -1]->mv_prime, nodesFinal, edges);
    a = a + T_uv_Zero(u, nodesFinal[post_v -1]->mv_prime, nodesFinal, edges);
    a = a - Ruv1(u, v, nodesFinal, edges);
    a = a - T_uv_Zero(u, v, nodesFinal, edges);
    return a;

}

int B_uvt(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){

    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v, nodesFinal, edges);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int net_min =MAX_SIZE;
    for(int x=mv-1; x<mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x, nodesFinal)); i<minimum(t, tree_size(x, nodesFinal)); i++){
            Node* ex = nodesFinal[x-1]->node;
            int a = T_u_t(i, ex, nodesFinal, edges);
            a = a + Luvt(t-i, ex, u, nodesFinal, edges);
            a = a + Ruv1(u, ex, nodesFinal, edges);
            a = a - Ruv1(u, v, nodesFinal, edges);
            a = a - T_uv_Zero(u, v, nodesFinal, edges);

            if(a<min)   min= a;
        }
        if(min<net_min) net_min = min;
    }
    return net_min;

}

int L_uvt_theo3(Node* u, Node* v, int t, vector<ObjectL1*> nodesFinal, vector<Edge*> edges){
    int a = A_uvt(u, v, t, nodesFinal, edges);
    int b = B_uvt(u, v, t, nodesFinal, edges);
    return minimum(a, b);
}

void Proxies(Node* u, int t, vector<ObjectL1*> vec, vector<edges> edge_vec)
{
    if(t==1)
    {
        cout<<u->post_order_number<<endl;
        return;
    }
    else
    {
        int mv=vec[u->post_order_number-1]->mv->post_order_number;      //post order no of Mv of u
        for(int v=mv;v<=u->post_order_number;v++)
        {
            int tv1=Tv1(vec[u->post_order_number-1]->node, vec, edge_vec);
            int tuv0=T_uv_Zero(u, vec[v-1]->node, vec, edge_vec);
            int ruv1=Ruv1(u,  vec[v-1]->node, vec, edge_vec);
            int luv0=Luv0(u,  vec[v-1]->node, vec, edge_vec);


        }

        for(int t=2;t<=k;t++)
        {
            for(int v=mv;v<=u->post_order_number;v++)
            {
                if(v==mv)
                {
                    int luvtt=L_uvt_theo3(u,  vec[v-1]->node,t-1, vec, edge_vec);
                    //Calculate x and c

                }
            }
        }


    }


}

/*
int main() 
{
// your code goes here
	
	//////////////////////////////INPUT STARTS////////////////////////////////////////////////
	int n; cin>>n;
	int graph[n][n]; 					//THIS IS DIRECTED TREE
	for(int i1=0;i1<n;i1++)
	{
		for(int j1=0;j1<n;j1++)
		{
		  int x; cin>>x;
		  graph[i1][j1]=x;
	}
	vector<int> weights; 					//WEIGHT OF EACH NODE
	for(int i11=0;i11<n;i11++)
	{
		int x;
		cin>>x;
		weights.push_back(x);
	}
		
	///////////////////////////////INPUT OVER///////////////////////////////////////////////////////
	if(n!=0)					//if Number of nodes are >0 (Obviously)
	{
		Node* root=new Root(weights[0]);
		Tree* tree=new Tree(root);
		//Post-Order Traversal							
		ObjectL1 postOrderTraversal[n]=L1(graph*);		//Create a class ObjectL1. THIS OBJECT CONTAINS A NODE(REFERENCE), Mv, Mv'
									//An array made of objects of class ObjectL1 is returned
		
		
			
	}
	else return -1;
}
		
return 0;
}
*/

//this main is to test the L1 function
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
} 
  
// A utility function to print the adjacency list 
// representation of graph 
void printGraph(vector<int> adj[], int V) 
{ 
    for (int v = 0; v < V; ++v) 
    { 
        cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : adj[v]) 
           cout << "-> " << x; 
        printf("\n"); 
    } 
} 

#endif