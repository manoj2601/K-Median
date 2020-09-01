#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "allclasses.h"
// #include "helperfunctions.h"
#include <iostream>
#define MAX_SIZE INT_MAX
#define ARR_SIZE 1024

using namespace std;


int Cu[ARR_SIZE], Nu[ARR_SIZE];
int Tut[ARR_SIZE][ARR_SIZE]; //1st : post order number of u && 2nd : t
int TV1[ARR_SIZE], TUV0[ARR_SIZE], RUV1[ARR_SIZE], LUV0[ARR_SIZE];
int LUVt[ARR_SIZE][ARR_SIZE];	//first is v and second is t
int XUVt[ARR_SIZE][ARR_SIZE], CUVt[ARR_SIZE][ARR_SIZE];	//first is v and second is t

vector < int >proxyList;
vector < int >CuList;
vector < int >NuList;


vector<Node*> nodes(1024); //acc to init_number
vector <Edge*> edge_vec;
vector<ObjectL1*> obj_vec;				//vector conataining nodes in post order

int mv_init_number[ARR_SIZE];
int mvp_init_number[ARR_SIZE];

int Luvt(Node* u, Node* v, int t);//int t, Node* v, Node* u, vector<ObjectL1*> nodesFinal, vector<Edge*> edges);



Node* find_mv(Node* current_node)
{
    if(mv_init_number[current_node->ini_number] != -1)
        return nodes[mv_init_number[current_node->ini_number]];
    if((current_node->node_child).size() == 0)
        {
            mv_init_number[current_node->ini_number] = current_node->ini_number;
            return current_node;
        }
        mv_init_number[current_node->ini_number] = find_mv((current_node->node_child)[0])->ini_number;
        return nodes[mv_init_number[current_node->ini_number]];
}

Node* find_mvPrime(Node* current_node)
{
    Node* dummy = new Node(-1, nullptr, -1);
    if(mvp_init_number[current_node->ini_number] != -1)
        return nodes[mvp_init_number[current_node->ini_number]];
    Node* mv = find_mv(current_node);//nodes[mv_init_number[current_node->ini_number]];
    int i=mv->post_order_number-1;
    if(i<=0)
        return dummy;
    while(true)
    {
        if(obj_vec[i-1]->node->node_child.size() == 0)
            return obj_vec[i-1]->node;
        i--;
        if(i<0)
            return dummy;
    }
    return dummy;
}


void L1(Node* root, int &node_number)    //array is passed by reference. //vec is vector conataining nodes in post order 
{
    //base case1: when the only node is root
    if((root->node_child).size() == 0 &&  (root->parent) == nullptr)
	{
        ObjectL1* obj ;
        Node* mv = find_mv(root);//nodes[mv_init_number[root->ini_number]];
        // Node* mvp = find_mvPrime(root);//nodes[mvp_init_number[root->ini_number]];
        obj = new ObjectL1(root, mv, node_number+1);
        node_number += 1;
        obj_vec.push_back(obj);
        return;
    }

    //base case2: when the node is the leaf node.
    if((root->node_child).size() == 0){
        //cout<<"leaf node\n";
        ObjectL1* obj;
        Node* mv = find_mv(root);//nodes[mv_init_number[root->ini_number]];
        // Node* mvp = find_mvPrime(root);//nodes[mvp_init_number[root->ini_number]];
        obj = new ObjectL1(root, mv, node_number+1);
        
        node_number += 1;
        obj_vec.push_back(obj);
        return;
    }

    //recursive program.
    int size = (root->node_child).size();
    for(int i=0; i< size; i++)
        L1((root->node_child)[i], node_number);
        Node* mv = find_mv(root);//nodes[mv_init_number[root->ini_number]];
        // Node* mvp = find_mv(root);//nodes[mvp_init_number[root->ini_number]];
    ObjectL1* obj = new ObjectL1(root, mv, node_number+1);
    node_number += 1;
    obj_vec.push_back(obj);
    return;
}

int search_edge(Node* s, Node* d)
{//search whether an edge is present or not.
    if(s->parent == d)
    {
        return s->parentEdgeWeight;
    }
    else return -1;
    // if(edge_vec.size() == 0)
    //     return -1;
    // for(int i=0; i<edge_vec.size(); i++)
    // {
    //     if(s == edge_vec[i]->firstNode && d == edge_vec[i]->secondNode)
    //         return edge_vec[i]->length;
    // }
    // return -1;

    // int size = edge_vec.size();
    // Edge* obj;
    // if(size ==0)
    // return -1;
    // for(int i=0; i<size; i++){
    //     obj = edge_vector[i];
    //     Node* a = obj->firstNode;
    //     Node* b = obj->secondNode;
    //     if(a==x && b==u)
    //     return obj->length;
    // }
    // return -1;
}
int distance(Node* x, Node* u)
{
    // cout<<" x is : "<<x->ini_number<<" u is : "<<u->ini_number<<endl;
    Node* child = x;
    Node* parent = child->parent;
    // cout<<child->parent->ini_number<<endl;
    int dist = 0;
    int  y=0;
    if(x->ini_number == u->ini_number){
        // cout<<"Here"<<endl;
        return 0;
    }
    while(parent!=u ){
        y = search_edge(child, parent);
        if(y == -1)
            {
                cout<<"Impossibledistance1"<<endl;
                exit(1);
            }
        dist += y;
        child = parent;
        parent = child->parent;
    }
    y = search_edge(child, parent);
    if(y == -1)
        {
            cout<<"Impossibledistance2"<<endl;
            exit(1);
        }
    dist += y;
    return dist;
}

int T_uv_Zero(Node* u, Node* v)
{
    Node* mv = find_mv(v);//nodes[mv_init_number[v->ini_number]];
    int mvpo = mv->post_order_number;
    int loopend = v->post_order_number;
    int ret = 0;

    for(int i=mvpo; i<=loopend; i++){
        int wt = obj_vec[i-1]->node->weight;
        ret += wt * distance(obj_vec[i-1]->node, u);
    }
    return ret;

}

int Tv1(Node* v) 
{
    return T_uv_Zero(v, v);
}

int Ruv1(Node* u, Node* v)   //u: parent node;, v: child node
{
    int end = u->post_order_number;
    int start = 1+v->post_order_number;
    int ret=0;
    for(int i=start; i<=end; i++)
    {
        int w = obj_vec[i-1]->node->weight;
        ret += w*distance(obj_vec[i-1]->node, u);
    }
    return ret;
}

int Luv0(Node* u, Node* v)
{
    int i = v->post_order_number;
    int j = u->post_order_number;
    int mv=((obj_vec[i-1])->mv)->post_order_number;
    int mu=((obj_vec[j-1])->mv)->post_order_number;
    int ret=0;
    for(int k=mu; k<mv; k++)
    {
        int w=obj_vec[k-1]->node->weight;
        ret+=w * distance(obj_vec[k-1]->node, u);
    }
    return ret;
}


int minimum(int a, int b){
    if(a<b)
        return a;
    else b;
}

// int minimum(int x, int y) 
// { 
//   return (x <= y) ? x : y ;
// } 

int maximum(int a, int b){
    if(a<b)
    return b;
    return a;
}

int tree_size(int u)
{
    int mu = (obj_vec[u-1])->mv->post_order_number;
    return u-mu+1;
}

int LuvSize(int u, int v){
    int mv = obj_vec[v-1]->mv->post_order_number;
    int mu = obj_vec[u-1]->mv->post_order_number;
    return mv-mu;
}

int T_u_t(int t, Node* u)
{   
    if(Tut[u->post_order_number][t] != 0)
    {
        return Tut[u->post_order_number][t];
    }
    Node* muNode = find_mv(u);//nodes[mv_init_number[u->ini_number]];
// cout<<"t: "<<t<<endl;
    if(t>= (u->post_order_number - muNode->post_order_number + 1))
    {
        Nu[u->post_order_number] = u->post_order_number-1;
        Cu[u->post_order_number] = tree_size(u->post_order_number)-1;
        return 0;
    }
    //base case.
    if(t == 1){
        int x = Tv1(u);
        // cout<<"IN BASE x is : "<<x<<endl;
        Tut[u->post_order_number][t] = x;
        return x;
    }

    //recursive
    int mu = muNode->post_order_number;
    int j = u->post_order_number;
    int y=MAX_SIZE;
    for(int v=mu; v<j; v++)
    {
        int CuValue = 1;
        int x=MAX_SIZE;   
        for(int l = maximum(1, t-1-LuvSize(j, v)); l<minimum(t, tree_size(v)); l++){
            // cout<<"l: "<<l<<endl;
            int a;
            if(Tut[v][l] == 0)
                a = T_u_t(l, (obj_vec[v-1])->node);
            else a = Tut[v][l];
            // cout<<"a: "<<a<<"  "<<"t-l-1: "<<t-l-1<<endl;
            if(LUVt[v][t-l-1] == 0)
                a = a + Luvt(u, obj_vec[v-1]->node, t-l-1);//t-l-1, (obj_vec[v-1])->mv, u);
            else a = a+LUVt[v][t-l-1];
            // cout<<"a after Luvt: "<<a<<endl;
            if(RUV1[v] == 0)
                a = a + Ruv1(u, (obj_vec[v-1])->node);
            else a = a+RUV1[v];
            // cout<<"a after Ruv1: "<<a<<endl;
            if(a<x)
            {
                x=a;
                CuValue = l;
            }
        }
        if(x<y)
        {
            y=x;
            Nu[u->post_order_number] = v;
            Cu[u->post_order_number] = CuValue;
        }
    }
    return y;
}

int Luvt(Node* u, Node* v, int t){//int t, Node* v, Node* u){
    //negative case
    if(t<0)
    return 0;

    if(t> (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int ret =MAX_SIZE;
    int CUVtValue = t-1;
    for(int x=mu; x<mv; x++){
        int min = MAX_SIZE;
        // cout<<"firstfor x "<<x<<endl;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x)); i<=minimum(t, tree_size(x)); i++)
        {
            // cout<<"second for i : "<<i<<endl;
            Node* ex = obj_vec[x-1]->node;
            int a = T_u_t(i, ex);
            if(LUVt[x][t-i] == 0)
                a = a + Luvt(u, ex, t-i);//t-i, ex, u);
            else a = a+LUVt[x][t-i];
            if(RUV1[x]==0)
                a = a + Ruv1(u, ex);
            else a = a + RUV1[x];
            if(RUV1[v->post_order_number] == 0)
                a = a - Ruv1(u, v);
            else a = a - RUV1[v->post_order_number];
            if(TUV0[v->post_order_number] == 0)
                a = a - T_uv_Zero(u, v);
            else a = a - TUV0[v->post_order_number];
            if(a<min)
            {
                CUVtValue = i;
                min= a;
            }
        }
        if(min<ret){
            XUVt[v->post_order_number][t] = x;
            CUVt[v->post_order_number][t] = CUVtValue;
            ret = min;
        }
    }
    // cout<<"happy"<<endl;
    if(ret != MAX_SIZE)
    return ret;
    // cout<<"see"<<endl;
    return 0;
}

int A_uvt(Node* u, Node* v, int t)
{
    int post_v = v->post_order_number;
    int a = Luvt(u, obj_vec[post_v -1]->mv_prime, t);//, , u);
    a = a + Ruv1(u, obj_vec[post_v -1]->mv_prime);
    a = a + T_uv_Zero(u, obj_vec[post_v -1]->mv_prime);
    a = a - Ruv1(u, v);
    a = a - T_uv_Zero(u, v);
    return a;
}

int B_uvt(Node* u, Node* v, int t){

    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;

    //base case
    if(t==0){
        return Luv0(u, v);
    }
    int mu = find_mv(u)->post_order_number;
    int mv = find_mv(v)->post_order_number;
    int net_min =MAX_SIZE;
    for(int x=mv-1; x<mv; x++){
        int min = MAX_SIZE;
        for(int i=maximum(1, t-LuvSize(u->post_order_number, x)); i<minimum(t, tree_size(x)); i++){
            Node* ex = obj_vec[x-1]->node;
            int a = T_u_t(i, ex);
            a = a + Luvt(u, ex, t-i);//t-i, ex, u);
            a = a + Ruv1(u, ex);
            a = a - Ruv1(u, v);
            a = a - T_uv_Zero(u, v);

            if(a<min)   min= a;
        }
        if(min<net_min) net_min = min;
    }
    return net_min;

}

int A_uvtManoj(Node* u, Node* v, int t)
{
    if(t>= (find_mv(v)->post_order_number - find_mv(u)->post_order_number))
        return 0;
    int mu = find_mv(u)->post_order_number;
    int mvp = find_mvPrime(v)->post_order_number;
    int y = MAX_SIZE;
    for(int x=mu; x<mvp; x++)
    {
        int y1 = MAX_SIZE;
        for(int l=maximum(1, LuvSize(u->post_order_number, x)); l<=minimum(t, tree_size(x)); l++)
        {
            int a = T_u_t(l, obj_vec[x-1]->node);
            a = a+Luvt(u, obj_vec[x-1]->node, t-l);//t-l, obj_vec[x-1]->node, u);
            a=a+Ruv1(u, obj_vec[x-1]->node);
            a = a - Ruv1(u, v);
            a = a - T_uv_Zero(u, v);
            if(a<y1) y1 = a;
        }
        if(y<y1) y = y1;
    }
    return y;
}

int L_uvt_theo3(Node* u, Node* v, int t){
    int a = A_uvtManoj(u, v, t);
    int b = B_uvt(u, v, t);
    return minimum(a, b);
}


void L3(int u_po)
{
    // cout<<"For u : "<<u_po<<endl;
	int mu = obj_vec[u_po - 1]->mv->post_order_number;
	for(int i=mu; i<=u_po; i++)
	{
        // cout<<"for i : "<<i<<endl;
        if(TV1[i] == 0)
		    TV1[i] = Tv1(obj_vec[i-1]->node);
        // cout<<"Tv1 : "<<TV1[i]<<" ";
		TUV0[i] = T_uv_Zero(obj_vec[u_po-1]->node, obj_vec[i-1]->node);
		// cout<<"Tuv0 : "<<TUV0[i]<<" ";
        RUV1[i] = Ruv1(obj_vec[u_po-1]->node, obj_vec[i-1]->node);
		// cout<<"RUV1 : "<<RUV1[i]<<" ";
        LUV0[i] = Luv0(obj_vec[u_po-1]->node, obj_vec[i-1]->node);
		// cout<<"LUV0 : "<<LUV0[i]<<" \n\n";
        Tut[i][1] = TV1[i];
        // cout<<"Tut1 : "<<Tut[i]<<endl<<endl;
	}
}

void L5(int u_po, int t) {
            int mu = obj_vec[u_po-1]->mv->post_order_number;
            for(int v = mu+1; v<u_po; v++)
            {
                // cout<<" t is "<<t<<" and v is "<<v<<endl;
                if(v == obj_vec[v-1]->mv->post_order_number)
                {
                    //L6
                    // cout<<"in if condition"<<endl;
                    LUVt[v][t-1] = Luvt(obj_vec[u_po-1]->node, obj_vec[v-1]->node, t-1);
                    // cout<<"LUVt[v][t-1] : "<<LUVt[v][t-1]<<endl;
                }
            }
}
void L4(int u_po, int k)
{
    // cout<<"IN L4 with u_po : "<<u_po<<" and k : "<<k<<endl;
	int mu = obj_vec[u_po-1]->mv->post_order_number;
	for(int t = 2; t<=k; t++)
	{
        L5(u_po, t);
		//L7
        Tut[u_po][t] = T_u_t(t, obj_vec[u_po-1]->node);
        // cout<<"for node : "<<u_po<<" and t : "<<t<<" Tut is : "<<Tut[u_po][t]<<endl;
	}
    // cout<<endl<<endl<<endl;
}


void Proxies(Node* u, int t)
{
    if(t==1)
    {
        // cout<<u->post_order_number<<endl;
        return;
    }
        int mu=obj_vec[u->post_order_number-1]->mv->post_order_number;      //post order no of Mv of u
        
		L3(u->post_order_number);
		L4(u->post_order_number, t);
        
        int nu1 = Nu[u->post_order_number];
        int cu1 = Cu[u->post_order_number];

        NuList.push_back(nu1);
        CuList.push_back(cu1);
        proxyList.push_back(nu1);

        int i = 2;
        int T = t-cu1-1;

        int nuprev = nu1;
        while(true)
        {
            int nui = XUVt[nuprev][T];
            int cui = CUVt[nuprev][T];
            if(cui != 0 && nui != 0)
            {
                NuList.push_back(nui);
                CuList.push_back(cui);
                proxyList.push_back(nui);
                nuprev = nui;
                T = T-cui;
                i++;
                if(T <= 0)
                    break;
            }
            else break;
        }
        return;



        // for(int t1=2;t1<=t; t1++)
        // {
        //     for(int v=mu; v<u->post_order_number-1; v++)
        //     {
        //         if(v==mu)
        //         {
        //             int luvtt=L_uvt_theo3(u,  obj_vec[v-1]->node, t1-1);
        //             //Calculate x and c

        //         }
        //     }
        // }
        
}


void L13()
{
    for(int i=0; i<NuList.size(); i++)
    {
        Proxies(obj_vec[NuList[i] - 1]->node, CuList[i]);
    }
    //upadated proxyList.
}

void L2(int k)
{
    for(int i=1; i<=obj_vec.size(); i++)
    {
        L3(i);
        L4(i, k);
    }
}

int main(int argc, char** argv) 
{
	// cout<<argv[1]<<endl;
	// return 0;
    int k = stoi(argv[1]);
        // cout<<"give k: "<<endl;
        // cin>>k;
        // int n=36;

	        // Node* root = new Node(0, nullptr, 0);
	        // nodes.push_back(root);
	        // Node* one = new Node(1, root, 1);
	        // nodes.push_back(one);
	        // Node* two = new Node(2, root, 2);
	        // nodes.push_back(two);
	        // Node* three = new Node(3, root, 3);
	        // nodes.push_back(three);
	        // Node* four = new Node(4, root, 4);
	        // nodes.push_back(four);
	        // Node* five = new Node(5, root, 5);
	        // nodes.push_back(five);
	        // (root->node_child).push_back(one) ;
	        // (root->node_child).push_back(two) ;
	        // (root->node_child).push_back(three) ;
	        // (root->node_child).push_back(four);
	        // (root->node_child).push_back(five) ;
	        // Node* six = new Node(6, one, 6);
	        // nodes.push_back(six);
	        // Node* seven = new Node(7, one, 7);
	        // nodes.push_back(seven);
	        // (one->node_child).push_back(six);
	        // (one->node_child).push_back(seven);
	        // Node* eight = new Node(8, five, 8);
            // nodes.push_back(eight);
	        // Node* nine = new Node(9, eight, 9);
            // nodes.push_back(nine);
	        // five->node_child.push_back(eight);
	        // eight->node_child.push_back(nine);


	        // Edge* one_ = new Edge(1, one, root);
	        // Edge* two_ = new Edge(1, two, root);
	        // Edge* three_ = new Edge(1, three, root);
	        // Edge* four_ = new Edge(1, four, root);
	        // Edge* five_ = new Edge(1, five, root);
	        // Edge* six_ = new Edge(1, six, one);
	        // Edge* seven_ = new Edge(1, seven, one);
	        // Edge* eight_ = new Edge(1, eight, five);
	        // Edge* nine_ = new Edge(1, nine, eight);
	        
	        // edge_vec.push_back(one_);
	        // edge_vec.push_back(two_);
	        // edge_vec.push_back(three_);
	        // edge_vec.push_back(four_);
	        // edge_vec.push_back(five_);
	        // edge_vec.push_back(six_);
	        // edge_vec.push_back(seven_);
	        // edge_vec.push_back(eight_);
	        // edge_vec.push_back(nine_);

//input start
    // int k;
    // cin>>k;
    ifstream infile;
    infile.open("cost.tree");
    int a;
    int count;
    while(infile>>a)
    {
    	count++;
    	string temp;
    	infile>>temp;
        int cost;
        infile>>cost;
        Node* obj = new Node(cost, nullptr, a);
        nodes[a] = obj;
    }
    infile.close();
    ifstream infile2;
    infile.open("adjencylist.tree");
    string line;
    while(getline(infile, line))
    {
        stringstream str(line);
        string word;
        str>>word;
        int a = stoi(word);
        
        string dir;
        str>>dir;
        int c;
        while(str>>word)
        {
        	c = stoi(word);
            nodes[a]->add_child_in_node(nodes[c]);
            nodes[c]->parent = nodes[a];
            nodes[c]->parentEdgeWeight = 1;
            Edge* e = new Edge(1, nodes[c], nodes[a]);
            edge_vec.push_back(e);
        }
    }
    infile2.close();
    Node* root = nodes[0];
        // cout<<"tut checking : "<<Tut[10][10]<<endl;
		//filling mv_init_number
        for(int i=0; i<count; i++)
        {
            mv_init_number[i] = -1;
            mvp_init_number[i] = -1;
        }
		// cout<<"Nodes : "<<nodes.size()<<endl;


		//INPUT DONE
		cout<<" k is : "<<k<<endl;
	        int node_number = 0;
	        L1(root, node_number);
        for(int i=0; i<count; i++)
		{
			Node* mvp = find_mvPrime(nodes[i]);
            obj_vec[nodes[i]->post_order_number-1]->mv_prime = mvp;
			mvp_init_number[i] = mvp->ini_number;
			cout<<"Manoj"<<endl;
		}
		cout<<count<<endl;
        // int j=0;
        // cout<<j++<<endl;
        // cout<<j++<<endl;
        // for(int j = 0; j < count; j++)
        // {
        // 	cout<<j<<endl;
        // }
         cout<<"CHECKED!!"<<"\n\n\n\n"<<endl;
			//In case, there are more proxies than nodes
		    ofstream outfile1;
    outfile1.open("proxies.txt",  ios::out|ios::app);
        ofstream outfile2;
    outfile2.open("costs.txt",  ios::out|ios::app);
			if (k >= obj_vec.size ())
			{
				for (int i = 0; i < obj_vec.size (); i++)
				{
					outfile1 << nodes[i]->ini_number <<" ";
				}
				outfile1<<endl;
				outfile2<<0<<endl;
				return 0;
			}
            L2(k);
            
			//PHASE 1 complete
	        
			//phase 2 start

			proxyList.push_back(obj_vec.size()); //mark root as proxy
			Proxies(obj_vec[obj_vec.size()-1]->node, k); //root and k
            L13();
            set<int> proxySet;
            // cout<<"Proxys are : "<<endl;
            for(int i=0; i<proxyList.size(); i++)
            {
                proxySet.insert(obj_vec[proxyList[i]-1]->node->ini_number);
                // cout<<obj_vec[proxyList[i]-1]->node->ini_number<<" ";
            }
            // cout<<endl;
            // sort(proxyArray, proxyArray + proxyList.size());
            for(int i : proxySet)
            	outfile1<<i<<" ";
            // for(int i=0; i<proxyList.size(); i++)
            //     outfile1<<proxyArray[i]<<" ";
            outfile1<<endl;
            outfile1.close();
            outfile2<<Tut[obj_vec.size()][k]<<endl;
            outfile2.close();
		// 	int size = obj_vec.size();

	    //     //check T_uv_zero
	    //     int apple =0;
	    //     apple = T_uv_Zero(root, one);
	    //     cout<<"T_uv_zero for node one: "<<apple<<endl;
	
	    //     apple = Tv1(root, vec, edge_vec);
	    //     cout<<"Tv1 for root: "<<apple<<endl;
	    //     apple = Ruv1(root, three, vec, edge_vec);
	    //     cout<<"Ruv1 for node three: "<<apple<<endl;
	    //     apple = Luv0(root, five, vec, edge_vec);
	    //     cout<<"Luv0 for node five: "<<apple<<endl;
	
	    //     int Tv1Array[size];
	    //     int T_uv_0Array[size];
	    //     int Ruv1Array[size];
	    //     int Luv0Array[size];
	    //     //initialization
	    //     for(int i=0; i<size; i++){
	    //         Tv1Array[i] = -1;
	    //         T_uv_0Array[i] = -1;
	    //         Ruv1Array[i] = -1;
	    //         Luv0Array[i] = -1;
	    //     }

	    //     //array dec
	    //     int array[size][k];
	        
	    //     for (int u = 1; u <= size;u++)
	    //     {	
	    // //////////////////////////////////////////////L2//////////////////////////
	        	
	    // //////////////////////////////////////////////L3//////////////////////////
	    //         int mvOfU=vec[u-1]->mv->post_order_number;
	    //         cout<<"FOR NODE "<<u<<" WHOSE MV= "<<mvOfU<<":"<<endl;
	    //         cout<<"Entering into the subtree Tu=T"<<u<<" :"<<endl;
	    //         for(int v=mvOfU; v<=u; v++)                 //v belongs to Tu
	    //         {	
	    //         	cout<<"node under observation is "<<v<<endl;
	    //             int mvv = (vec[v-1]->mv)->post_order_number;
	                
	    //             int Tv11=Tv1(vec[v-1]->node);		//take inputs the length of each edge and prepare a adjacency matrix for that
	    //                                             //also prepare a vector of weights of vertices
	    //             cout<<"||Tv||1= "<<Tv11<<endl;
	    //             int valTuv0 = T_uv_Zero(vec[u-1]->node, vec[v-1]->node);    //value of valTuv0 is updated
	    //             cout<<"||Tu,v||0= "<<valTuv0<<endl;
	    //             int ruv1=Ruv1(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
	    //             cout<<"||Ru,v||1= "<<ruv1<<endl;
	    //             int luv0=Luv0(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
		// 			cout<<"||Lu,v||0= "<<luv0<<endl;
	    //             //storing T_uv_Zero
	    //             Tv1Array[u-1] = Tv11;
	    //             // cout<<"value of Tv1Array set to "<<Tv1Array[u-1]<<endl;
	    //             T_uv_0Array[u-1] = valTuv0;
	    //             // cout<<"value of T_uv_0Array set to "<<T_uv_0Array[u-1]<<endl;
	    //             Ruv1Array[u-1] = ruv1;
	    //             // cout<<"value of Ruv1Array set to "<<Ruv1Array[u-1]<<endl;
	    //             Luv0Array[u-1] = luv0;
	    //             // cout<<"value of Luv0Array set to "<<Luv0Array[u-1]<<endl;

	    //             // cout<<"v is "<<vec[v-1]->node->post_order_number<<" with mv= "<<mvv<< " ||Tv||1= "<<Tv11<<" value of ||Tu,v||0= "<<valTuv0<<" ||Ru, v||1="<<ruv1<<" ||Lu,v||0= "<<luv0<<endl;
	    //         }
	    // ///////////////////////////////////////////////L3/////////////////////////
	    // ///////////////////////////////////////////////L4///////////////////////
		// 		cout<<"u= "<<u<<endl;
	    //         for(int t=2;t<=k;t++)
	    //         {
	    //             int mvOfu=vec[u-1]->mv->post_order_number ;
        //             cout<<"t= "<<t<<endl;
	    // ///////////////////////////////////L4/////////////////////////////////
	    // ///////////////////////////////////////////////L5/////////////////////            
	    //             if(t>=u-mvOfu+1){
		// 				int T_ut=0;

		// 				cout<<"||Tu||t= "<<T_ut<<endl;
		// 				break;
	    //             }
					
		// 			else{
		//                 for (int v = mvOfu+1; v <= u-1 ; v++)
		//                 {
		//     ///////////////////////////////////////////////L5//////////////////////////////////////////
		//     ///////////////////////////////////////////////L6//////////////////////////////////////////
		//                     // code //
		//                     int mv=vec[v-1]->mv->post_order_number;
		//                     if(v==mv)
		//                     {

		//                         int luvt1=L_uvt_theo3(vec[u-1]->node, vec[v-1]->node, t-1, vec, edge_vec);
		//                       	cout<<"For node v= "<<v<<" ||Luv||"<<t-1<<"= "<<luvt1<<endl;
		//                     }
		//                 }
		//     ///////////////////////////////////////////////L6///////////////////////////////////////////////
		                
		//     ///////////////////////////////////////////////L7/////////////////////////////////////////////
		//                 int T_ut = T_u_t(t, vec[u-1]->node, vec, edge_vec);
		//                 array[u-1][k-1] = T_ut;

		//                 cout<<"For t= "<<t<<" value of T_ut= "<<T_ut<<endl;
	    //         	}
	    // ///////////////////////////////////////////////L7///////////////////////////////
	    //         }
				
	    // ///////////////////////////////////////////////L8//////////////////////////
	    // //CHECK: how to calculate Tvt for v=[1, u] & t=[1,k]            
	    //         for(int j=0; j<size; j++){
	    //             int tv1 = Tv1(vec[j]->node, vec, edge_vec);
	    //             array[j][0] = tv1;
	    //         }
	    //         cout<<endl<<endl;
	    // 	}
			/*
	    ////////////////////////////////////////////////L8/////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////
            //                  PHASE 2

            // Node* ro=vec[0]->node;
            // Proxies(ro, k, vec, edge_vec);

           */ 
            cout<<"THANKS\n";
	return 0;

}
