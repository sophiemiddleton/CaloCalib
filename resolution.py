import uproot
import matplotlib.pyplot as plt
import math
import numpy as np


file = uproot.open("paraFile.root")
Pions = file["newTree;1"]
dfpos = Pions.pandas.df(flatten=False)

fig, ax = plt.subplots(1,1)

resolution = []
for i,j in enumerate(dfpos["Peak"]):
  resolution.append(dfpos["Peak"]-6.13)
npos, bins, patches = ax.hist(resolution,
                           bins=100,
                           range=(-0.5,0.5),
                           label="WASB",histtype='step')

ax.set_yscale('log')

ax.set_ylabel('Entries/bin')
ax.set_xlabel('Resolution')


fig.show()
fig.savefig("resolution.eps")
