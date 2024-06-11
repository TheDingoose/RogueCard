extends Node3D
@export var stoobid = SimpleCard.new()
@export var stoobidArray:Array = stoobid.get_effect_array()
@export var stoobidCost = stoobid.get_card_cost()
@export var stoobidDescription = stoobid.get_card_description()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _init():
	stoobid.set_effect_array(stoobidArray)
	stoobid.set_card_cost(stoobidCost)
	stoobid.set_card_description(stoobidDescription)
	pass
