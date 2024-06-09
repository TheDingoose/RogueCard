extends Node3D
@export var stoobid = SimpleCard.new()
@export var stoobidArray:Array = stoobid.m_effect
@export var stoobidCost = stoobid.Get_card_cost()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _init():
	stoobid.Set_Effect_Array(stoobidArray)
	stoobid.Set_card_cost(stoobidCost)
	pass
