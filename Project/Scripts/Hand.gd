extends Node2D

@export var cards: Array
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
	if is_dragging_card:
		dragging_card.position = get_local_mouse_position()
		#TODO: IF we are not too far from our hand
		cards.erase(dragging_card)
		cards.insert(get_card_space_from_position(dragging_card.position) ,dragging_card)
	pass

func update_hovering_card(card_visuals):
	if hovering_cards.has(card_visuals):
		hovering_cards.erase(card_visuals)
	else:
		hovering_cards.append(card_visuals)

func play_card(grid_position):
	if dragging_card.card_data.use_card(grid_position, $"..".grid):
		#TODO: Remove card cost from resource? Or will card to this itself?
		print("Playing " + dragging_card.name + "onto " + str(grid_position))
		discard_pile.append(dragging_card)
		#TODO: probably wanna disable the visuals and collision instead
		dragging_card.position = Vector2i(9999,9999)
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
	var total_cards = cards.size()
	var cards_start_offset = position.x - (total_cards * 0.5 * CARD_SPACING )
	var current = 0.5
	for i in cards:
		i.position = Vector2i(cards_start_offset + (current * CARD_SPACING), 0)
		i.z_index = current
		current += 1
	pass

func get_card_space_from_position(target_positions):
	var hand_position = get_viewport().get_visible_rect().size
	hand_position.x *= 0.25
	position = hand_position
	var total_cards = cards.size()
	var cards_start_offset = position.x - (total_cards * 0.5 * CARD_SPACING )
	return clampi((int)((target_positions.x - cards_start_offset) / CARD_SPACING), 0, total_cards)

func draw_card():
	var card = card_visuals_base.instantiate()
	add_child(card)
	var card_data = BaseCard.new()
	card.card_data = card_data
	#TODO: Assign card visuals by data, probably something for the cardcore scene itself
	
	card.get_mouse_detecting_area().mouse_entered.connect(update_hovering_card.bind(card))
	card.get_mouse_detecting_area().mouse_exited.connect(update_hovering_card.bind(card))
	
	cards.push_back(card)
	
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
				if highest_found < cards.find(i):
					highest_found = cards.find(i)
			
			if highest_found >= 0:
				dragging_card = cards[highest_found]
				is_dragging_card = true
				print("Dragging; " + dragging_card.name)
			else:
				print("Problem occured grabbing card from hand")
		else:
			if is_dragging_card: 
				play_card(get_mouse_grid_position())
			is_dragging_card = false
			space_cards()
#TODO: And if card is far enough away from the hand, otherwise put it in that place in hand instead
