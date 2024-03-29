extends Node3D

var marker = load("res://Marker.tscn")
var radius = 0
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
				var dir = camera3d.project_ray_normal(event.position)
				var dist = absf(from.y) / absf(dir.y)
				var planepoint = round(from + dir * dist)
				var planepoint2d = Vector2i(planepoint.x, planepoint.z)
				#var coords = grid.get_hollow_circle_coords(planepoint2d, radius, radius + 7)
				#var coords = grid.get_circle_coords(planepoint2d, radius)
				var coords = grid.get_halo_coords(planepoint2d, radius)
				var boys = grid.get_array_data(grid.get_circle_coords(planepoint2d, 2), false)
				
				#var coords = grid.get_square_coords(planepoint2d,Vector2i(radius, radius))
				radius = radius + 1
				var co = 0.0
				for c in boys: 
					print(c)
					print(c.name)
					
					
					#print(c)
					#var spawned = marker.instantiate()
					#spawned.update_colour(float(co) / float(coords.size()))
					#add_child(spawned)
					#spawned.set_global_position(Vector3(c.x, 0, c.y))
					#co = co + 1
					#await get_tree().create_timer(0.1).timeout
					#print(float(co) / float(coords.size()))
				#print("------")
				
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
