#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "allclasses.h"
#include "helperfunctions.h"
#define MAX_SIZE INT_MAX
using namespace std;

int main() 
{
    // your code goes here
        // Node* null_node = new Node(-1, NULL);
        //////////////////INPUT START///////////////////////
        	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	        // int n=1000;
            // vector<int> adj[n]; 	
	        // vector<Node*> allnodes;	
	        // for(int i=0; i<1000; i++)	
	        // {	
	        //     Node* n = new Node(-1, nullptr);	
	        //     (n->initialid) = i;	
	        //     allnodes.push_back(n);	
	        // }	
	        // //taking inputs start	
	        // int k = 10;//edge value	
	        // ifstream infile; //taking input of all parent-child nodes	
	        // infile.open("/home/ash/Downloads/trace.tree", in);	
	        // string line;	
	        // while(getline(infile, line))	
	        // {	
	        //     stringstream check1(line);	
	        //     int parent;	
	        //     check1 >> parent;	
	        //     string arrow;	
	        //     check1>>arrow;	
	        //     vector<int> child_nodes;	
	        //     int child;	
	        //     while(check1>>child)	
	        //     {	
	        //         child_nodes.push_back(child);	
		
	        //         (allnodes[child]->parent) = allnodes[parent];	
	        //         (allnodes[parent]-> node_child).push_back(allnodes[child]);	
	        //     }	
	        // }	
	        // Node* root = allnodes[0];	
	        // infile.close();	
	        // ifstream infile2; //taking input of the weight of the nodes	
	        // infile2.open("/home/ash/Downloads/trace.cost", in);	
	        // while(getline(infile2, line))	
	        // {	
	        //     stringstream check1(line);	
	        //     int n; //index of node in allnodes	
	        //     int weight; //weight of nth node in allnodes	
	        //     string arrow;	
	        //     check1>>n;	
	        //     check1>>arrow;	
	        //     check1>>weight;	
	        //     (allnodes[n]->weight) = weight;	
	        // }	
	        // //taking inputs over	
	        // //creating graph (adjacency matrix)	
	        // int graph[1000][1000];	
	        	
	        // for(int i=0; i<1000; i++)	
	        // {	
	        //     int a[1000];	
	        //     for(int j=0; j<1000; j++)	
	        //     {	
	        //         graph[i][j] = 0;	
	        //     }	
	        // }	
		
		
		
		
		
		
		
	        // for(int i=0; i<allnodes.size(); i++)	
	        // {	
	        //     for(int j=0; j<(allnodes[i]->node_child).size(); j++)	
	        //     {	
	        //         graph[(allnodes[i]->node_child)[j].initialid][i] = k;	
	        //     }	
		
	        // }		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k=9;
        // cout<<"give k: "<<endl;
        // cin>>k;
        int n=10;
            vector<Node*> nodes;
	        Node* root = new Node(0, nullptr);
	        nodes.push_back(root);
	        Node* one = new Node(1, root);
	        nodes.push_back(one);
	        Node* two = new Node(2, root);
	        nodes.push_back(two);
	        Node* three = new Node(3, root);
	        nodes.push_back(three);
	        Node* four = new Node(4, root);
	        nodes.push_back(four);
	        Node* five = new Node(5, root);
	        nodes.push_back(five);
	        (root->node_child).push_back(one) ;
	        (root->node_child).push_back(two) ;
	        (root->node_child).push_back(three) ;
	        (root->node_child).push_back(four);
	        (root->node_child).push_back(five) ;
	        Node* six = new Node(6, one);
	        nodes.push_back(six);
	        Node* seven = new Node(7, one);
	        nodes.push_back(seven);
	        (one->node_child).push_back(six);
	        (one->node_child).push_back(seven);
	        Node* eight = new Node(8, five);
	        Node* nine = new Node(9, eight);
	        five->node_child.push_back(eight);
	        eight->node_child.push_back(nine);

            	        vector <Edge*> edge_vec;
	        Edge* one_ = new Edge(1, one, root);
	        Edge* two_ = new Edge(1, two, root);
	        Edge* three_ = new Edge(1, three, root);
	        Edge* four_ = new Edge(1, four, root);
	        Edge* five_ = new Edge(1, five, root);
	        Edge* six_ = new Edge(1, six, one);
	        Edge* seven_ = new Edge(1, seven, one);
	        Edge* eight_ = new Edge(1, eight, five);
	        Edge* nine_ = new Edge(1, nine, eight);
	        
	        edge_vec.push_back(one_);
	        edge_vec.push_back(two_);
	        edge_vec.push_back(three_);
	        edge_vec.push_back(four_);
	        edge_vec.push_back(five_);
	        edge_vec.push_back(six_);
	        edge_vec.push_back(seven_);
	        edge_vec.push_back(eight_);
	        edge_vec.push_back(nine_);

        
        int graph[n][n];				//Adjaceny matrix of the tree
        
        // cin>>n;
        graph[1][0]=10;
        graph[2][0]=10;
        graph[3][0]=10;
        graph[4][0]=10;
        graph[5][0]=10;
        graph[6][1]=10;
        graph[7][1]=10;
        vector<Edge*> edges;                //VECTOR CONTAINING EDGES
        for (int i = 0; i < n; i++)
        {
            /* code */
            // vector<int> v;
            for (int i1 = 0; i1 < n; i1++)
            {
                /* code */
                // v.push_back(graph[i][i1]);
                if(graph[i][i1]!=0)
                {
                    Edge* e=new Edge(graph[i][i1], nodes[i], nodes[i1]);
                    edges.push_back(e);
                }

            }

            //  cout<<"node number: "<<obj->node_number<<endl;
            // graph1[i]=v;
        }
    /////////////////////////////////INPUT OVER//////////////////////////////////////////////

    /////////////////////////////////////L1//////////////////////////////////////////
         vector<ObjectL1*> vec;				//vector conataining nodes in post order
	        int node_number = 0;
	        // cout<<"start\n";
	        L1(root, vec, node_number);
	        int size = vec.size();
	        if(size==node_number){
	            // cout<<"hurrah!\n";
	        }
	        for(int i=0; i<size; i++){
	            ObjectL1* obj = vec[i];
	            int wt = (obj->node)->weight;
	            int wt1 = (obj->mv)->weight;
	            int wt2;
	            if(obj->mv_prime == nullptr)
	            wt2 =-1;
	            else
	            wt2 = (obj->mv_prime)->weight;
	            // cout<<"weight of node: "<<wt<<"\n";
	            // cout<<"weight of mv: "<<wt1<<"\n";
	            // cout<<"weight of mv_prime: "<<wt2<<"\n";
	            // cout<<"node number: "<<obj->node_number<<endl;
	            // cout<<"post_order_number: "<<(obj->node)->post_order_number<<endl<<endl;
	        }
	
	        // cout<<"size of vec is "<<vec.size()<<endl;
	        // for(int i=0;i<vec.size();i++)
	        // {
	            
	        //     cout<<"node "<<vec[i]->node->weight<<", number is "<<vec[i]->node_number;
	        //     if(vec[i]->node->parent!=nullptr)
	        //     cout<<", with its parent as "<<vec[i]->node->parent->weight;
	        //     cout<<endl;
	        // }
	
	        //check T_uv_zero
	        int apple =0;
	        // apple = T_uv_Zero(root, three, vec, edge_vec);
	        // cout<<"T_uv_zero for node four: "<<apple<<endl;
	
	        // apple = Tv1(root, vec, edge_vec);
	        // cout<<"Tv1 for root: "<<apple<<endl;
	        // apple = Ruv1(root, three, vec, edge_vec);
	        // cout<<"Ruv1 for node four: "<<apple<<endl;
	        // apple = Luv0(root, three, vec, edge_vec);
	        // cout<<"Luv0 for node four: "<<apple<<endl;
	
	        int Tv1Array[size];
	        int T_uv_0Array[size];
	        int Ruv1Array[size];
	        int Luv0Array[size];
	        //initialization
	        for(int i=0; i<size; i++){
	            Tv1Array[i] = -1;
	            T_uv_0Array[i] = -1;
	            Ruv1Array[i] = -1;
	            Luv0Array[i] = -1;
	        }

	        //array dec
	        int array[size][k];
	        
	        for (int u = 1; u <= size;u++)
	        {	
	    //////////////////////////////////////////////L2//////////////////////////
	        	
	    //////////////////////////////////////////////L3//////////////////////////
	            int mvOfU=vec[u-1]->mv->post_order_number;
	            cout<<"FOR NODE "<<u<<" WHOSE MV= "<<mvOfU<<":"<<endl;
	            // cout<<"Entering into the subtree Tu=T"<<u<<" :"<<endl;
	            for(int v=mvOfU;v<=u;v++)                 //v belongs to Tu
	            {	
	            	// cout<<"node under observation is "<<v<<endl;
	                int mvv = (vec[v-1]->mv)->post_order_number;
	                
	                int Tv11=Tv1(vec[v-1]->node, vec, edge_vec);		//take inputs the length of each edge and prepare a adjacency matrix for that
	                                                //also prepare a vector of weights of vertices
	                // cout<<"||Tv||1= "<<Tv11<<endl;
	                int valTuv0 = T_uv_Zero(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);    //value of valTuv0 is updated
	                // cout<<"||Tu,v||0= "<<valTuv0<<endl;
	                int ruv1=Ruv1(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
	                // cout<<"||Ru,v||1= "<<ruv1<<endl;
	                int luv0=Luv0(vec[u-1]->node, vec[v-1]->node, vec, edge_vec);
					// cout<<"||Lu,v||0= "<<luv0<<endl;
	                //storing T_uv_Zero
	                Tv1Array[u-1] = Tv11;
	                // cout<<"value of Tv1Array set to "<<Tv1Array[u-1]<<endl;
	                T_uv_0Array[u-1] = valTuv0;
	                // cout<<"value of T_uv_0Array set to "<<T_uv_0Array[u-1]<<endl;
	                Ruv1Array[u-1] = ruv1;
	                // cout<<"value of Ruv1Array set to "<<Ruv1Array[u-1]<<endl;
	                Luv0Array[u-1] = luv0;
	                // cout<<"value of Luv0Array set to "<<Luv0Array[u-1]<<endl;

	                // cout<<"v is "<<vec[v-1]->node->post_order_number<<" with mv= "<<mvv<< " ||Tv||1= "<<Tv11<<" value of ||Tu,v||0= "<<valTuv0<<" ||Ru, v||1="<<ruv1<<" ||Lu,v||0= "<<luv0<<endl;



	            }
	    ///////////////////////////////////////////////L3/////////////////////////
	    ///////////////////////////////////////////////L4///////////////////////
				cout<<"u= "<<u<<endl;
	            for(int t=2;t<=k;t++)
	            {
	                int mvv=vec[u-1]->mv->post_order_number ;
                    cout<<"t= "<<t<<endl;
	    ///////////////////////////////////L4/////////////////////////////////
	    ///////////////////////////////////////////////L5/////////////////////            
	                if(t>=u-mvv+1){
						int T_ut=0;

						cout<<"||Tu||t= "<<T_ut<<endl;
						break;
	                }
					
					else{
		                for (int v = mvv+1; v <= u-1 ; v++)
		                {
		    ///////////////////////////////////////////////L5//////////////////////////////////////////
		    ///////////////////////////////////////////////L6//////////////////////////////////////////
		                    /* code */
		                    int mv=vec[v-1]->mv->post_order_number;
		                    if(v==mv)
		                    {

		                        int luvt1=L_uvt_theo3(vec[u-1]->node, vec[v-1]->node, t-1, vec, edge_vec);
		                      	cout<<"For node v= "<<v<<" ||Luv||"<<t-1<<"= "<<luvt1<<endl;
		                    }
		                }
		    ///////////////////////////////////////////////L6///////////////////////////////////////////////
		                
		    ///////////////////////////////////////////////L7/////////////////////////////////////////////
		                int T_ut = T_u_t(t, vec[u-1]->node, vec, edge_vec);
		                array[u-1][k-1] = T_ut;

		                cout<<"For t= "<<t<<" value of T_ut= "<<T_ut<<endl;
	            	}
	    ///////////////////////////////////////////////L7///////////////////////////////
	            }
				
	    ///////////////////////////////////////////////L8//////////////////////////
	    //CHECK: how to calculate Tvt for v=[1, u] & t=[1,k]            
	            for(int j=0; j<size; j++){
	                int tv1 = Tv1(vec[j]->node, vec, edge_vec);
	                array[j][0] = tv1;
	            }
	            cout<<endl<<endl;
	    	}
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

            

	return 0;

}
