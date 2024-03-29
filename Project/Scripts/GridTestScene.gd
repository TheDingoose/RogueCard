extends Node3D

var grid
var RAY_LENGTH = 100
var selected = null

# Called when the node enters the scene tree for the first time.
func _ready():
	grid = get_node("/root/GlobalGrid")
	grid.load_grid($LoaderGrid);
	$LoaderGrid.queue_free()
	pass # Replace with function body.

func _input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == 1:
		var camera3d = $Camera3D
		var from = camera3d.project_ray_origin(event.position)
		var to = from + camera3d.project_ray_normal(event.position) * RAY_LENGTH
		if selected == null: #if we dont have a thing selected
			var space_state = get_world_3d().direct_space_state
			var query = PhysicsRayQueryParameters3D.create(from, to)
			query.collide_with_areas = true;
			query.collide_with_bodies = true;
			var result = space_state.intersect_ray(query)
			if !result.is_empty():
				#print(result["collider"].get_parent().name + " selected!")
				selected = result["collider"].get_parent()
				
		else:
			#find ray direction
			var dir = camera3d.project_ray_normal(event.position)
			var dist = absf(from.y) / absf(dir.y)
			var planepoint = round(from + dir * dist)
			var planepoint2d = Vector2i(planepoint.x, planepoint.z)
			print(planepoint2d)
			selected.safe_move_on_grid(planepoint2d, grid)
			selected = null

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	get_viewport().get_mouse_position()
	#if clicked on a GridObject, set var to that
	#if clicked on empty cell with Gridobject Selected, move to there
	pass
