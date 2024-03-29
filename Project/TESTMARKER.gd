extends Node3D

var colour = Color(0,0,1,0.5);
var limit = 50.0
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func update_colour(f):
	
	#var r = (float(f) / limit)
	#var g = maxf(0, float(f) - limit)/limit
	#var b = maxf(0, float(f) - limit * 2.0)/(limit * 2.0)
	
	
	#colour = Color(r, g, b, 0.5)
	colour.h = (float(f))
	var matt = get_child(0).mesh.material.duplicate()
	matt.albedo_color = colour
	
	
	get_child(0).mesh.material = matt
	#$MeshInstance3D
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
