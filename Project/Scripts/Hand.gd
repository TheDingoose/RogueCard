extends Node2D

@export var cards: Dictionary
const CARD_SPACING = 150
var card_visuals_base = preload("res://Scenes/UI/Card/CardBase.tscn")

var discard_pile: Array

@export var camera: Camera3D
const RAY_LENGTH = 100


var hovering_cards: Array
var dragging_card
var is_dragging_card = false

# Called when the node enters the scene tree for the first time.
func _ready():
	camera = get_viewport().get_camera_3d()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func update_hovering_card(card_visuals):
	if hovering_cards.has(card_visuals):
		hovering_cards.erase(card_visuals)
	else:
		hovering_cards.append(card_visuals)

func play_card(grid_position):
	if cards[dragging_card].use_card(grid_position, $"..".grid):
		#TODO: Remove card cost from resource? Or will card to this itself?
		print("Playing " + dragging_card.name + "onto " + str(grid_position))
		discard_pile.append(cards[dragging_card])
		cards.erase(dragging_card)
		space_cards()
	else:
		print("Invalid play, playing " + dragging_card.name + "onto " + str(grid_position))
	dragging_card = null
	is_dragging_card = false
	pass

func space_cards():
	var hand_position = get_viewport().get_visible_rect().size
	hand_position.x *= 0.25
	position = hand_position
	var total_cards = cards.keys().size()
	var cards_start_offset = position.x - (total_cards * 0.5 * CARD_SPACING )
	var current = 0.5
	for i in cards.keys():
		i.position = Vector2i(cards_start_offset + (current * CARD_SPACING), 0)
		current += 1
	pass

func draw_card():
	var card_visuals = card_visuals_base.instantiate()
	add_child(card_visuals)
	var card_data = BaseCard.new()
	
	#TODO: Assign card visuals by data, probably something for the cardcore scene itself
	
	card_visuals.get_mouse_detecting_area().mouse_entered.connect(update_hovering_card.bind(card_visuals))
	card_visuals.get_mouse_detecting_area().mouse_exited.connect(update_hovering_card.bind(card_visuals))
	cards[card_visuals] = card_data
	
	space_cards()
	
	pass

func get_mouse_grid_position():
	var mousepos = get_viewport().get_mouse_position()
	var from = camera.project_ray_origin(mousepos)
	var to = from + camera.project_ray_normal(mousepos) * RAY_LENGTH
	var dir = camera.project_ray_normal(mousepos)
	var dist = absf(from.y) / absf(dir.y)
	var planepoint = round(from + dir * dist)
	var planepoint2d = Vector2i(planepoint.x, planepoint.z)
	return planepoint2d
	pass

func _input(event):
	if event is InputEventMouseButton and event.button_index == 1:
		if event.pressed :
			if hovering_cards.size() == 0: 
				return
			#wichever is last in the cards dict keys array should be on top
			var highest_found = -1
			for i in hovering_cards:
				if highest_found < cards.keys().find(i):
					highest_found = cards.keys().find(i)
			
			if highest_found >= 0:
				dragging_card = cards.keys()[highest_found]
				is_dragging_card = true
				print("Dragging; " + dragging_card.name)
			else:
				print("Problem occured grabbing card from hand")
		else:
			if is_dragging_card: 
				play_card(get_mouse_grid_position())
			is_dragging_card = false
#TODO: And if card is far enough away from the hand, otherwise put it in that place in hand instead
