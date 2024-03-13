@tool
extends GridObject

# Called when the node enters the scene tree for the first time.
func _ready():
	set_on_grid(Vector2i(round(global_position.x), round(global_position.z)), $"../LoaderGrid")
	if Engine.is_editor_hint():
		set_notify_transform(true)
	else:
		#set_on_grid(get_grid_pos(), get_node("/root/GlobalGrid"));
		set_notify_transform(false)
pass # Replace with function body.

func _notification(notif):
	if (notif == NOTIFICATION_TRANSFORM_CHANGED && Engine.is_editor_hint()):
		var twodPos = Vector2(global_position.x, global_position.z)
		if (Vector2(Vector2(get_grid_pos()) - twodPos).length() >= 1):
			print("set")
			
			var RoundedPos = Vector2i(round(global_position.x), round(global_position.z))
			print($"../LoaderGrid".get_cell_data(RoundedPos))
			print($"../LoaderGrid".get_cell_ID(RoundedPos))
			safe_move_on_grid(RoundedPos, $"../LoaderGrid")
			print($"../LoaderGrid".get_cell_data(RoundedPos))
			print($"../LoaderGrid".get_cell_ID(RoundedPos))
	
	
	# safe_move_on_grid(RoundedPos)
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
