#! /usr/bin/env Rscript
png("convex.png", width=700, height=700)
plot(1:10000, 1:10000, type="n")

#points
points(5342,978)
points(9233,6906)
points(8349,1995)
points(2680,9076)
points(4686,8213)
points(8872,212)
points(1326,7889)
points(4840,4454)
points(9653,2051)
points(6403,3653)

#line segments
segments(5342,978,8872,212)
segments(5342,978,1326,7889)
segments(9233,6906,2680,9076)
segments(9233,6906,9653,2051)
segments(2680,9076,1326,7889)
segments(8872,212,9653,2051)
dev.off()
