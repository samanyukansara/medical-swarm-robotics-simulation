define counter position
(
	# stove
	block
	(
		points 4
		point[0] [0 0]#
		point[1] [0 16]  
		point[2] [-8 16]
		point[3] [-8 0]
		z [0 1]

	)
	# counter bottom
	block
	(
		points 4
		point[0] [0 0]#
		point[1] [-17 0]  
		point[2] [-17 -8]
		point[3] [0 -8]
		z [0 1]

	)
	# counter top
	block
	(
		points 4
		point[0] [0 16]#
		point[1] [0 24]  
		point[2] [-24 24]
		point[3] [-24 16]
		z [0 1]

	)

	#fit shape to this size in meters
	size [24 24 5.5]
	drive "diff"
	mylaser(pose [ 0.050 0.000 0.000 0.000 ])
)
