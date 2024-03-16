@tool
extends EditorPlugin

var dock
#This should open and activate all the other tools

func _enter_tree():
	# Initialization of the plugin goes here.
	dock = preload("res://addons/grid_tools/GridToolDock.tscn").instantiate()
	add_control_to_dock(DOCK_SLOT_LEFT_BR, dock)
	
	
	pass


func _exit_tree():
	# Clean-up of the plugin goes here.
	remove_control_from_docks(dock)
	dock.free()
	pass
