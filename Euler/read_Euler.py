import numpy as np
import matplotlib.pyplot as plt

import matplotlib as mpl
def format(fig):
    mpl.rcParams['font.family'] = 'STIXGeneral'
    plt.rcParams['xtick.labelsize'] = 19
    plt.rcParams['ytick.labelsize'] = 19
    plt.rcParams['font.size'] = 19
    plt.rcParams['figure.figsize'] = [5.6*6, 4*3]
    plt.rcParams['axes.titlesize'] = 18
    plt.rcParams['axes.labelsize'] = 18
    plt.rcParams['lines.linewidth'] = 2
    plt.rcParams['lines.markersize'] = 6
    plt.rcParams['legend.fontsize'] = 15
    plt.rcParams['mathtext.fontset'] = 'stix'
    plt.rcParams['axes.linewidth'] = 1.5
    # plt.style.use('dark_background')


def ax_format(ax, xmaj, xmin, ymaj, ymin):
    ax.xaxis.set_tick_params(which='major', size=5, width=1,
                            direction='in', top='on')
    ax.xaxis.set_tick_params(which='minor', size=3, width=1,
                            direction='in', top='on')
    ax.yaxis.set_tick_params(which='major', size=5, width=1,
                            direction='in', right='on')
    ax.yaxis.set_tick_params(which='minor', size=3, width=1,
                            direction='in', right='on')
    ax.xaxis.set_major_locator(mpl.ticker.MultipleLocator(xmaj))
    ax.xaxis.set_minor_locator(mpl.ticker.MultipleLocator(xmin))
    ax.yaxis.set_major_locator(mpl.ticker.MultipleLocator(ymaj))
    ax.yaxis.set_minor_locator(mpl.ticker.MultipleLocator(ymin))

fig1 = plt.figure(figsize=(10,10))
format(fig1)

ax1 = fig1.add_subplot(1, 1, 1)
ax_format(ax1, 0.5e-13, 0.1e-13, 0.5e-13, 0.1e-13)


name_list = ["1", "7.5", "30", "45", "100", "-1", "-7.5", "-30", "-45", "-100"]
for i in range(len(name_list)):
    x1_list = []
    y1_list = []
    lineN = 0

    with open("output_"+name_list[i]+".txt") as f:
        for line in f.readlines():
            s = line.split(',')
            lineN = lineN + 1
            x1_list.append(float(s[0]))
            y1_list.append(float(s[1]))
    x1 = np.array(x1_list)
    y1 = np.array(y1_list)
    ax1.plot(x1[::1],y1[::1],'-o',linewidth=1,markersize=2,label=name_list[i]+" $\mathrm{fm}$")

ax1.plot(0,0,'o', markersize=5, color='goldenrod')
ax1.text(0.03e-13,0.03e-13,"$\mathrm{Au^{+79}}$",fontsize=12,color='goldenrod')
#plt.plot(x1[::50],y1[::50],'.',markersize=5,label='RKa')
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.set_title("Rutherford scattering simulated by Euler-Cromer method \n under different impact parameters")
ax1.set_ylim(-0.2e-12,0.2e-12)
ax1.set_xlim(-0.15e-12,0.15e-12)
ax1.legend()
ax1.grid()
plt.savefig('Rutherford_scattering_Euler.png')


