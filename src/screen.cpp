#include "api.h" 
#include "storage.h"
#include "main.h"

namespace screen {

	using namespace pros;
	using namespace std;

	void message_box(const char *);

	//Create a button descriptor string array
	static const char * red_btnm_map[] = {
		"Alpha", "Bravo", "Charlie", "Delta", "Echo", "\n",
		"Foxtrot", "Golf", "Hotel", "India", "Juliett", ""
	};

	static const char * blue_btnm_map[] = {
		"Kilo", "Lima", "Mike", "November", "Oscar", "\n",
		"Papa", "Quebec", "Romeo", "Sierra", "Tango", ""
	};

	static const char * skill_btnm_map[] = {
		"Uniform", "Victor", "Whiskey", "\n",
		"Xray", "Yankee", "Zulu", ""
	};

	static const char * action_btnm_map[] = {
		"Record", "Clear", ""
	};

	lv_obj_t * btn_matrix_group[3];
	const char * selected_program;
	void (*notif_handler)(const char *, const char *) = NULL;

	void set_notif_handler(void (*handler)(const char *, const char *)) {
		notif_handler = handler;
	}

	void notif(const char * rumble_msg, const char * msg) {
		if (notif_handler != NULL) {
			notif_handler(rumble_msg, msg);
		}
	}

	void do_saving() {
		std::string msg = "Program ";
		msg += selected_program;
		msg += " saved";
		vector<recording::RecordUnit>& dump = recording::dump();
		if (storage::save_to_slot(dump, selected_program)) {
			message_box(msg.c_str());
			notif(".", "Save!!");
		} else {
			message_box("Unable to save");
			notif("-", "!!Unable to save!!");
		}
	}

	void do_recording() {
		bool is_skill_profile = false;
		int size = sizeof(skill_btnm_map) / sizeof(skill_btnm_map[0]);
		for (int i=0; i<size; ++i) {
			if (strcmp(skill_btnm_map[i], selected_program) == 0) {
				is_skill_profile = true;
				break;
			}
		}
		int record_duration = is_skill_profile ? 60000 : 15000;
		recording::reset(record_duration, ITERATION_INTERVAL, do_saving);
		notif(".", "Starting ...");
	}

	void do_clear() {
		storage::clear_slot(selected_program);
	}

	static lv_res_t confirm_box_callback(lv_obj_t *btns, const char *txt) {
		if (txt == "Yes") {
			cout << "confirm to clear " << selected_program << endl;
			do_clear();
		}
		lv_obj_t * mbox = lv_mbox_get_from_btn(btns);
		lv_obj_t * gray_bg = lv_obj_get_parent(mbox);
		lv_obj_del(gray_bg);

		return LV_RES_INV;
	}

	void confirm_box(const char * message, const char * action_name) {
		static lv_style_t gray_style;
		lv_style_copy(&gray_style, &lv_style_plain);
		gray_style.body.opa = LV_OPA_70;
		gray_style.body.main_color = LV_COLOR_HEX3(0x111);
		gray_style.body.grad_color = LV_COLOR_HEX3(0x111);

		lv_obj_t * gray_bg = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_style(gray_bg, &gray_style);
		lv_obj_set_size(gray_bg, LV_HOR_RES, LV_VER_RES);

		static const char * buttons[] = { "Yes", "Cancel", "" };
		lv_obj_t * mbox = lv_mbox_create(gray_bg, NULL);
		lv_mbox_set_text(mbox, message);
		lv_mbox_add_btns(mbox, buttons, confirm_box_callback);
		lv_obj_set_width(mbox, 200);
		lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/
	}

	void message_box(const char * message) {
		static const char * buttons[] = { "" };
		lv_obj_t * mbox = lv_mbox_create(lv_scr_act(), NULL);
		lv_mbox_set_text(mbox, message);
		lv_mbox_add_btns(mbox, buttons, NULL);
		lv_obj_set_width(mbox, 200);
		lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/
		lv_mbox_start_auto_close(mbox, 2000);
	}

	static lv_res_t action_selector_callback(lv_obj_t *btnm, const char *txt) {
		cout << txt << " on " << selected_program << endl;
		if (txt == "Record") {
			if (storage::is_slot_taken(selected_program)) {
				message_box("Slot already taken!!");
			} else {
				message_box("Record will auto start \nwhen you move the bot.");
				do_recording();
			}
		} else if (txt == "Clear") {
			if (storage::is_slot_taken(selected_program)) {
				std::string msg = "Are you sure to clear ";
				msg += selected_program;
				msg += "?";
				confirm_box(msg.c_str(), txt);
			} else {
				message_box("Nothing to clear");
			}
		}
		return LV_RES_OK;
	}

	static lv_res_t alphabet_selector_callback(lv_obj_t *btnm, const char *txt) {
		auto toggled_id = lv_btnm_get_toggled(btnm);
		auto pressed_id = lv_btnm_get_pressed(btnm);
		if (toggled_id == pressed_id) {
			return LV_RES_OK;
		} else {
			lv_btnm_set_toggle(btnm, true, pressed_id);
		}

		for (int i=0; i<3; ++i) {
			if (btn_matrix_group[i] != btnm) {
				uint16_t toggled_button_id = lv_btnm_get_toggled(btn_matrix_group[i]);
				if (toggled_button_id != LV_BTNM_PR_NONE) {
					lv_btnm_set_toggle(btn_matrix_group[i], false, toggled_button_id);
				}
			}
		}
		selected_program = txt;
		cout << "Program " << txt << " selected!" << endl;
		return LV_RES_OK;
	}

	lv_obj_t * add_button_matrix_to_tab(lv_obj_t * tab, const char ** btnm_map) {
		lv_obj_t * btn_matrix = lv_btnm_create(tab, NULL);
		lv_btnm_set_map(btn_matrix, btnm_map);
		// lv_btnm_set_toggle(btn_matrix, true, LV_BTNM_PR_NONE);
		lv_btnm_set_action(btn_matrix, alphabet_selector_callback);
		// lv_obj_set_size(btn_matrix, LV_HOR_RES, LV_VER_RES / 2);
		lv_obj_set_size(btn_matrix, 460, 100);
		lv_obj_set_pos(btn_matrix, 0, 0);
		lv_obj_align(btn_matrix, NULL, LV_ALIGN_CENTER, 0, 0);

		lv_obj_t *actBtnm = lv_btnm_create(tab, NULL);
		lv_btnm_set_map(actBtnm, action_btnm_map);
		lv_btnm_set_action(actBtnm, action_selector_callback);
		lv_obj_set_size(actBtnm, 300, 40);
		lv_obj_set_pos(actBtnm, 0, 230);
		lv_obj_align(actBtnm, NULL, LV_ALIGN_CENTER, 0, 0);	

		return btn_matrix;
	}

	vector<recording::RecordUnit>& load_replaying() {
		static vector<recording::RecordUnit> empty;
		if (storage::is_slot_taken(selected_program)) {
			return storage::get_program(selected_program);
		} else {
			return empty; 
		}
	}

	void setup_screen()
	{
		pros::delay(50); // sometimes LVGL won't draw the screen if there is no delay or it is not inverted on the brain

		// lvgl theme
		lv_theme_t *th = lv_theme_alien_init(280, NULL); //Set a HUE value and keep font default
		lv_theme_set_current(th);

		// create a tab view object
		lv_obj_t *tabview;
		tabview = lv_tabview_create(lv_scr_act(), NULL);

		// add 3 tabs (the tabs are page (lv_page) and can be scrolled
		const char * tab_names[3] = { "Red", "Blue", "Skills"};
		const char ** tab_button_matrix_names[3] = { red_btnm_map, blue_btnm_map, skill_btnm_map };
		for (int i=0; i<3; ++i) {
			lv_obj_t * tab = lv_tabview_add_tab(tabview, tab_names[i]);
			lv_style_t * style = lv_tabview_get_style(tab, LV_TABVIEW_STYLE_BG);
			style->body.padding.ver = 5;
			style->body.padding.hor = 10;
			btn_matrix_group[i] = add_button_matrix_to_tab(tab, tab_button_matrix_names[i]);
		}

		recording::set_replay_loader(load_replaying);
	}
}
