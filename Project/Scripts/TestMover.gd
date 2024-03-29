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
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
