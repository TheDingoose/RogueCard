@tool
extends Sprite2D

@export var card_info: BaseCard
@export var flipped:bool = false : set = _set_flipped

# Called when the node enters the scene tree for the first time.
func _ready():
	#$MouseDetecting/DetectingShape.shape.size = $".".texture.
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func get_mouse_detecting_area():
	return $MouseDetecting

func _set_flipped(value):
	flipped = value
	$Back.visible = flipped
	pass
