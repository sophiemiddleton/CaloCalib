import uproot
import matplotlib.pyplot as plt
import math
import numpy as np
import seaborn as sns
file = uproot.open("paraFile.root")
Pions = file["newTree;1"]
df = Pions.pandas.df(flatten=False)

sns.pairplot(df)# x_vars = ["Peak","Width","ChiSquared"], y_vars = ["Peak","Width","ChiSquared"])

plt.savefig("pairs.eps")
plt.show()
