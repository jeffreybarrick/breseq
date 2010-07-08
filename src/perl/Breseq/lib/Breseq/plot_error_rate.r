## Args should be in_file=/path/to/input/error_rates.tab out_file=/path/to/output


for (e in commandArgs()) {
  ta = strsplit(e,"=",fixed=TRUE)
  if(! is.na(ta[[1]][2])) {
    temp = ta[[1]][2]
 #   temp = as.numeric(temp) #Im only inputting numbers so I added this to recognize scientific notation
    if(substr(ta[[1]][1],nchar(ta[[1]][1]),nchar(ta[[1]][1])) == "I") {
      temp = as.integer(temp)
    }
    if(substr(ta[[1]][1],nchar(ta[[1]][1]),nchar(ta[[1]][1])) == "N") {
      temp = as.numeric(temp)
    }
    assign(ta[[1]][1],temp)
    cat("assigned ",ta[[1]][1]," the value of |",temp,"|\n")
  } else {
    assign(ta[[1]][1],TRUE)
    cat("assigned ",ta[[1]][1]," the value of TRUE\n")
  }
}


X<-read.table(in_file, sep="\t", header=T)
Y<-X

pdf(out_file, height=6, width=9)

A_col = "green";
A_pch = 15;
C_col = "red"; 
C_pch = 15;
T_col = "blue"; 
T_pch = 15;
G_col = "black"; 
G_pch = 15;
._col = "orange"; 
._pch = 15;

new_plot <- function()
{
	#bottom, left, top, right
	par(mar=c(5,5,3,3));
	options(warn=-1)
	plot(0, type="n", lty="solid", log="y", ylim=c(0.00000001, 1), xlim=c(min(X$quality), max(X$quality)), lwd=1, axes=F, xlab="", ylab="", las=1, cex.lab=1.2, cex.axis=1.2 )
	options(warn=1)
	box()
	#y-axis
	axis(2, cex.lab=1.2, las=1, cex.axis=1.2, yaxs="i", at = c(0.00000001, 0.0000001, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1), label = c(expression(10^-8), expression(10^-7), expression(10^-6), expression(10^-5), expression(10^-4), expression(10^-3), expression(10^-2), expression(10^-1), expression(1)))
	title(ylab="error rate", mgp = c(3.5, 1, 0), cex.lab=1.2)
	#x-axis
	axis(1, cex.lab=1.2, cex.axis=1.2, xaxs="i")
	title(xlab="base quality score", mgp = c(3, 1, 0), cex.lab=1.2)
}

new_plot()
lines(Y$quality, Y$AC, col=C_col)
points(X$quality, X$AC, pch=C_pch, col=C_col)

lines(Y$quality, Y$AT, col=T_col)
points(X$quality, X$AT, pch=T_pch, col=T_col)

lines(Y$quality, Y$AG, col=G_col)
points(X$quality, X$AG, pch=G_pch, col=G_col)

lines(Y$quality, Y$A., col=._col)
points(X$quality, X$A., pch=._pch, col=._col)

new_plot()
lines(Y$quality, Y$TA, col=A_col)
points(X$quality, X$TA, pch=A_pch, col=A_col)

lines(Y$quality, Y$TC, col=C_col)
points(X$quality, X$TC, pch=C_pch, col=C_col)

lines(Y$quality, Y$TG, col=G_col)
points(X$quality, X$TG, pch=G_pch, col=G_col)

lines(Y$quality, Y$T., col=._col)
points(X$quality, X$T., pch=._pch, col=._col)

new_plot()
lines(Y$quality, Y$CA, col=A_col)
points(X$quality, X$CA, pch=A_pch, col=A_col)

lines(Y$quality, Y$CT, col=T_col)
points(X$quality, X$CT, pch=T_pch, col=T_col)

lines(Y$quality, Y$CG, col=G_col)
points(X$quality, X$CG, pch=G_pch, col=G_col)

lines(Y$quality, Y$C., col=._col)
points(X$quality, X$C., pch=._pch, col=._col)

new_plot()
lines(Y$quality, Y$GA, col=A_col)
points(X$quality, X$GA, pch=A_pch, col=A_col)

lines(Y$quality, Y$GT, col=T_col)
points(X$quality, X$GT, pch=T_pch, col=T_col)

lines(Y$quality, Y$GC, col=C_col)
points(X$quality, X$GC, pch=C_pch, col=C_col)

lines(Y$quality, Y$G., col=._col)
points(X$quality, X$G., pch=._pch, col=._col)

new_plot()
lines(Y$quality, Y$.A, col=A_col)
points(X$quality, X$.A, pch=A_pch, col=A_col)

lines(Y$quality, Y$.T, col=T_col)
points(X$quality, X$.T, pch=T_pch, col=T_col)

lines(Y$quality, Y$.C, col=C_col)
points(X$quality, X$.C, pch=C_pch, col=C_col)

lines(Y$quality, Y$.G, col=G_col)
points(X$quality, X$.G, pch=G_pch, col=G_col)

dev.off()
