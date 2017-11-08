#!/usr/bin/env python3.6
import networkx as nx
import math

fname = "netscience"
G = nx.read_gml(fname+".gml")

print(nx.number_of_nodes(G))	
print(nx.number_of_edges(G))


Gn = nx.convert_node_labels_to_integers(G,first_label=0)
#print(Gn.nodes())

# create parsed edge list

# with open(fname+"_parsedw.txt","w") as f:
# 	for e in nx.generate_edgelist(Gn,data=['value']):
# 		print(e)
# 		f.write(e+'\n')

#for e in nx.generate_adjlist(G):
#	print(e)

if True:
	with open(fname+"_degree_centrality.txt","w") as f:

		cent = nx.degree_centrality(Gn)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))

if True:
	with open(fname+"_betweenness_centrality.txt","w") as f:

		cent = nx.betweenness_centrality(Gn)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))

if True:
	with open(fname+"_eigenvector_centrality_numpy.txt","w") as f:

		cent = nx.eigenvector_centrality_numpy(Gn)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))


if True:
	with open(fname+"_eigenvector_centrality.txt","w") as f:

		cent = nx.eigenvector_centrality(Gn)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))

if True:
	with open(fname+"_katz_centrality_numpy.txt","w") as f:

		cent = nx.katz_centrality_numpy(Gn)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))

if True:
	with open(fname+"_katz_centrality.txt","w") as f:

		cent = nx.katz_centrality(Gn,max_iter=10000,tol=1e-02)

		for n,c in sorted(cent.items()):
			print("%d %.6f"%(n,c))
			f.write("%d %.6f\n"%(n,c))
			
