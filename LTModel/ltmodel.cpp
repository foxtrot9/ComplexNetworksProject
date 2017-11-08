#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct {
	int nodes;	// Number of nodes
	float **adjMat;	// Adjacency Matrix
} Graph;

Graph *makeGraph(int nodes) {
	Graph *g1 = new Graph();
	g1->nodes = nodes;
	/* allocate the matrix */
	g1->adjMat = (float **) calloc(nodes,sizeof(float *));
	int i;
	for (i = 0; i < g1->nodes; ++i)
	{
		g1->adjMat[i] = (float *) calloc(nodes,sizeof(float));
	}
	return g1;
}

void normalizeGraph(Graph *g) {
	int i, j;
	float sum = 0;
	for (i = 0; i < g->nodes; ++i) {
		sum = 0;
		for (j = 0; j < g->nodes; ++j) {
			sum += g->adjMat[i][j];
		}
		if(sum > 0.001f) {
			for (j = 0; j < g->nodes; ++j) {
				g->adjMat[i][j] = g->adjMat[i][j] / sum;
			}
		}
	}
}

typedef struct{
	Graph *g;

	/**
		Represents threshold value for each 
		node above which it will accept 
		the idea(innovation).
	*/
	float *threshold;

	/*
		The time step at which a node
		accepts the idea(innovation).
	*/
	int *timeOfAdoption;

	int numberOfActivatedNodes;

	void setGraph(Graph *g1,float *threshold1){
		g = g1;
		threshold = threshold1;
		timeOfAdoption = new int[g->nodes];
		numberOfActivatedNodes = 0;
	}

	/**
		This function runs the linear threshold
		model given the initial set of activated 
		nodes. k is the number of initial activated nodes.
	*/
	int runModel(int *initNodes,int k){
		
		int i;
		for(i = 0;i < g->nodes ; i++){
			timeOfAdoption[i] = -1;
		}
	
		for(i = 0;i < k ; i++){
			timeOfAdoption[initNodes[i]] = 0;
		}
		
		int currActivations = k;
		int currTime = 1;
		numberOfActivatedNodes = currActivations;

		while(currActivations!=0){
			//cout<<numberOfActivatedNodes<<endl;
			currActivations = 0;

			vector<int> newlyActivatedNodes;

			for(i = 0;i < g->nodes;i++){
				if(timeOfAdoption[i]==-1){
					float weight = 0.0;
					for(int j = 0;j < g->nodes ; j++){
						if(timeOfAdoption[j]!=-1)
							weight+=g->adjMat[i][j];
					}
					if(weight>=threshold[i]){
						newlyActivatedNodes.push_back(i);
						currActivations++;
					}
				}
			}

			for(i = 0;i<newlyActivatedNodes.size();i++){
				timeOfAdoption[newlyActivatedNodes[i]] = currTime;
			}
			numberOfActivatedNodes+=currActivations;
			currTime++;
		}

		return numberOfActivatedNodes;
	}
} LTModel;

typedef struct{
	Graph *g;
	LTModel *ltModel;

	int *selected;
	int *initNodes;

	/**
		Model should be set up with graph
		and threshold values.
	*/
	void setModel(LTModel *model){
		ltModel = model;
		g = ltModel->g;

		selected = new int[g->nodes];
		int i;
		for(i = 0;i < g->nodes ; i++){
			selected[i] = 0;
		}

		initNodes = new int[g->nodes];
	}

	void selectBestInitialNodes(int k){

		int currProfit = 0;

		int i;
		for(i = 0;i < k;i++){
			cout<<"On step "<<i+1<<endl;

			int maxGain = -1;
			int maxGainNode = -1;

			int j;
			for(j=0;j<g->nodes;j++){
				if(selected[j]==0){
					initNodes[i] = j;

					int profit = ltModel->runModel(initNodes,i+1);
					int gain = profit-currProfit;
					if(gain>maxGain){
						maxGain = gain;
						maxGainNode = j;
					}
				}
			}

			currProfit+=maxGain;
			selected[maxGainNode] = 1;
			initNodes[i] = maxGainNode;
		}
	}
} LTHillClimbing;

float randomFloat(){
	float r = ((float) rand() / (RAND_MAX));
	return r;
}

void printGraph(Graph *g){
	for(int i=0;i<g->nodes;i++){
		for(int j=0;j<g->nodes;j++){
			cout<<g->adjMat[i][j]<<" ";
		}
		cout<<endl;
	}
}

void testLTModel(int k){
	int n,m;
	cin>>n>>m;

	Graph *g = makeGraph(n);

	for(int i=0;i<m;i++){
		int a,b;
		float w;
		cin>>a>>b>>w;
		g->adjMat[a][b] = w;
		g->adjMat[b][a] = w;
	}

	normalizeGraph(g);

	float *thres = new float[n];
	for(int i=0;i<n;i++){
		thres[i] = randomFloat();
	}

	LTModel *model = new LTModel();
	model->setGraph(g,thres);

	LTHillClimbing *hill = new LTHillClimbing();
	hill->setModel(model);
	hill->selectBestInitialNodes(k);

	for(int i=0;i<k;i++)
		cout<<hill->initNodes[i]<<" ";
	cout<<endl;

	/*int *initNodes = new int[n];
	for(int i=0;i<n;i++){
		initNodes[i] = i;
	}
	random_shuffle(initNodes,initNodes+n);*/
	
	cout<<model->runModel(hill->initNodes,k)<<endl;
}

void testBest30(){

	int n,m;
	cin>>n>>m;

	Graph *g = makeGraph(n);

	for(int i=0;i<m;i++){
		int a,b;
		float w;
		cin>>a>>b>>w;
		g->adjMat[a][b] = w;
		g->adjMat[b][a] = w;
	}

	normalizeGraph(g);

	float *thres = new float[n];
	for(int i=0;i<n;i++){
		thres[i] = randomFloat();
	}

	LTModel *model = new LTModel();
	model->setGraph(g,thres);


	string type;
	while(true){
		cin>>type;
		if(type=="over")
			break;

		cout<<type<<endl;

		int *initNodes = new int[30];
		for(int i=0;i<30;i++){
			cin>>initNodes[i];
			cout<<model->runModel(initNodes,i+1)<<endl;
		}
		cout<<endl;
	}
}

int main() {

	srand(26101996);
	//testLTModel(30);
	testBest30();

	return 0;
}