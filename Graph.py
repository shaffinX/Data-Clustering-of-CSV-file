import matplotlib.pyplot as lab
import pandas as pndlib
import numpy as nmpy 
import seaborn as seabn
graph = pndlib.read_csv("output1.csv")
seabn.scatterplot(x=graph.mean_dist_day, y=graph.mean_over_speed_perc, hue=graph.cluster, palette=seabn.color_palette("hls", n_colors=4))
lab.xlabel("Annual income (k$)")
lab.ylabel("Spending Score (1-100)")
lab.title("Clustered: spending (y) vs income (x)")

lab.show()