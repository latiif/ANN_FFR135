from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt


def drawPattern(pattern):

    fig = plt.figure()
    ax = mplot3d.Axes3D(fig)

    zdata = np.array([0,1,0,1,0,1,0,1])
    ydata = np.array([0,0,1,1,0,0,1,1])
    xdata = np.array([0,0,0,0,1,1,1,1])

    for item in range(len(pattern)):
        if pattern[item]=="1":
            ax.scatter3D(xdata[item], ydata[item], zdata[item],s=10, c='g',depthshade=False)
        else:
            ax.scatter3D(xdata[item], ydata[item], zdata[item], s=10, c='r', depthshade=False)

    # rotate the axes and update
    # for rotate the axes and update.
    plt.show()
    answer = input("Is this linearly separable?")
    if (answer=="1"):
        answer = True
    else:
        answer = False

    plt.close("all")

    return answer