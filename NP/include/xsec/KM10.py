import gepard as g
from gepard.fits import th_KM10b
import math as m
import random
import sys
import warnings

def main(args):
    xsec_mean=0
    phi_mean=0
    xB_mean=0
    t_mean=0
    Q2_mean=0
    N=1000
    n=0

    while(n<N):
        xB_val=random.uniform(args[4], args[5])
        Q2_val=random.uniform(max(args[2],(xB_val*(0.938**2 - 2.0**2)/(xB_val - 1.0))), min(args[3],2.0*0.938*xB_val*11))
        M=0.938
        num = Q2_val * M + (Q2_val / xB_val) * (Q2_val / (2 * M * xB_val) - m.sqrt(Q2_val + (Q2_val / (2 * M * xB_val))**2))
        den = M + Q2_val / (2 * M * xB_val) - m.sqrt(Q2_val + (Q2_val / (2 * M * xB_val))**2)                       
        tmin = -1.0*num/den
        t_val=random.uniform(max(args[0],-1.0), min(args[1],tmin))
        phi_val=random.uniform(args[6], args[7])*m.pi/180.

        pt = g.DataPoint(xB=xB_val, t=t_val, Q2=Q2_val, phi=phi_val, process="ep2epgamma", exptype='fixed target', in1energy=10.6, in1charge=-1,in1polarization=0,frame='Trento')
        pt.to_conventions()
        xsec_val=th_KM10b.XS(pt)

        if(not m.isnan(xsec_val)):
            n+=1
            xsec_mean+=1.0/xsec_val
            #print(phi_rad, xsecval)

    xB_mean=args[8] #xB_mean/N
    t_mean=args[9] #t_mean/N
    Q2_mean=args[10] #Q2_mean/N
    phi_mean=args[11]*m.pi/180. #phi_mean/N

    xsec_mean=n/xsec_mean
    pt = g.DataPoint(xB=xB_mean, t=t_mean, Q2=Q2_mean, phi=phi_mean, process="ep2epgamma", exptype='fixed target', in1energy=10.6, in1charge=-1,in1polarization=0,frame='Trento')
    pt.to_conventions()
    xsec_point=th_KM10b.XS(pt)
    
    #print(xsec_mean, xsec_point,phi_mean,xB_mean,t_mean,Q2_mean)
    return xsec_mean/xsec_point

if __name__ == "__main__":
    warnings.filterwarnings("ignore")
    args = [float(x) for x in sys.argv[1:]]     
    x =main(args)
    print(x)
