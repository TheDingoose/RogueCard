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
		var gridspace = $Hand.get_mouse_grid_position()
		if selected == null: #if we dont have a thing selected
			var result = grid.get_cell_id(gridspace)
			if is_instance_id_valid(result):
				selected = instance_from_id(result)
				#print(selected.name + " selected!")
		else:
			#find ray direction
			selected.safe_move_on_grid(gridspace, grid)
			selected = null
	elif event is InputEventKey:
		if event.keycode == KEY_D and event.pressed:
			$Hand.draw_card()
		elif event.keycode == KEY_F and event.pressed:
			if $Hand.is_dragging_card:
				$Hand.dragging_card.flipped = !$Hand.dragging_card.flipped

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
