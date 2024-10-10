#-------------------------------------------------------------------------
# Gnuplot script file for plotting data in file
# "postProcessing/sets/1/extract_Ax_Bz.xy" and analytic solution
# type in the terminal: $ gnuplot rodComparisonAxBz.plt
#------------------------------------------------------------------------- 
 
      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set term postscript eps color enh "Times-BoldItalic"
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically

#AxVSy:
      set title "x component of magnetic potential vector A VS radius "
      set xlabel "Radius (meters)"
      set ylabel "Ax"
      set output "rodAxVSy.ps"
      f(x)=(x<=9.9e-4) ? 0.000606129-(1.26e-6*19.086e+7*(x**2))/4 : 0.000606129-(1.26e-6*19.086e+7*(9.9e-4)**2)*(0.5+log(x/9.9e-4))/2
      #All the domain:
      #plot [0:999e-4]   "postProcessing/singleGraph/1/line_Ax_Bz.xy" \
      #Zoom-up:
      plot [0:0.01]   "postProcessing/singleGraph/1/line_Ax_Bz.xy" \
           using ($1):($2) \
           title "numerical solution", f(x) title "analytic solution"


#BzVSy:
      set output "rodBzVSy.ps"
      set title "z component of magnetic field B vs radius "
      set xlabel "Radius (meters)"
      set ylabel "Bz"
      Mu0=1.26e-6
      j=19.086e+7
      R=9.9e-4
      f(x)=(x<=9.9e-4) ? Mu0*j*x/2 : (Mu0*j*(R**2))/(2*x)
      #(1.26e-6*19.086e+7*x)/4 : (1.26e-6*19.086e+7*(9.9e-4)**2)/(2*x)
      #All the domain:
      #plot [0:999e-4] "postProcessing/singleGraph/1/line_Ax_Bz.xy" \
      #Zoom-up:
      plot [0:0.01] "postProcessing/singleGraph/1/line_Ax_Bz.xy" \
           using ($1):($3) \
           title "numerical solution", f(x) title "analytic solution"

