
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	共通選択メニュー
	-------------------------------------------------------
	ステージ選択メニュー
	ポーズ メニュー
	コンティニュー？メニュー
	-------------------------------------------------------
---------------------------------------------------------*/

#include "kaiwa_system.h"	/* 会話システムにSDL再描画指示。 */
#include "kanji_system.h"
//#include "common_menu.h"

enum
{
//	MENU_TYPE_00_SELECT_STAGE	= 0,
	MENU_TYPE_01_PAUSE	= 0,
	MENU_TYPE_02_ASK_CONTINUE,
	MENU_TYPE_99_MAX	/* メニューの数 */
};

#if 0
enum
{
	MENU_ITEM_00_CONTINUE_GAME	= 0,
	MENU_ITEM_01_RETRY_GAME,
	MENU_ITEM_02_QUIT_GAME,
	MENU_ITEM_99_MAX	/* オブジェクトの数 */
};

enum
{
	MENU_ITEM_00_CONTINUE_YES	= 0,
	MENU_ITEM_01_CONTINUE_NO,
	MENU_ITEM_99_MAX	/* オブジェクトの数 */
};
#endif

typedef struct
{
	u16 offset_x;	// 表示用 x オフセット */
	u16 offset_y;	// 表示用 y オフセット */
} MY_OFFSET;

#define SPEC_08_MENU_ITEM_MAX (8)
typedef struct
{
	MY_OFFSET		menu_item_my_obj[SPEC_08_MENU_ITEM_MAX];			/* オブジェクト */
	unsigned int	max_items;			/* オプションの項目数 */
	int 			selected_number;	/* 現在メニュー上で選択されている項目番号 */
	int 			menu_offset;		/* メニューのオフセット */
//
	int 			menu_brite; 		/* メニューの明るさ(α値) */
	int 			menu_type;			/* メニューの種類 */
} MENU;
static MENU aaa;

/*---------------------------------------------------------

---------------------------------------------------------*/

//	#define FPS_MENU_FACTOR8	(8*fps_factor)
	#define FPS_MENU_FACTOR8	(16)/* 8*FPS_MENU_FACTOR */

/*---------------------------------------------------------

---------------------------------------------------------*/

enum
{
//	MENU_RESOURCES_00_STAGE01 = 0,
//	MENU_RESOURCES_01_STAGE02,
//	MENU_RESOURCES_02_STAGE03,
//	MENU_RESOURCES_03_STAGE04,
//	MENU_RESOURCES_04_STAGE05,
//	MENU_RESOURCES_05_STAGE06,
//	MR_06_STOP,//----------------
	MENU_RESOURCES_07_CONTINUE = 0,
	MENU_RESOURCES_08_RESTART,
	MENU_RESOURCES_09_QUIT,
	MR_10_STOP,//----------------
	MENU_RESOURCES_11_YES,
	MENU_RESOURCES_12_NO,
	MR_13_STOP,//----------------
	MENU_RESOURCES_14_TITLE01,
	MENU_RESOURCES_15_TITLE02,
	MENU_RESOURCES_16_TITLE03,
	MENU_RESOURCES_16_TITLE04,
	MR_17_STOP,//----------------
	MENU_RESOURCES_99_MAX
};
typedef struct
{
	u16 x_offset;	// 表示用 x オフセット[pixel] */
	u16 y_offset;	// 表示用 y オフセット[pixel] */
	const char *str_name;
} MENU_RESOURCE;

static const MENU_RESOURCE my_menu_resource[/*8*/MENU_RESOURCES_99_MAX/*10*/] =
{
	//	RES01_STAGE_SELECT	/*const*/ char *stage_select_menu_options[] =/*(char *)*/stage_select_menu_options
//	{	360,				(113) +((0)*21),	"1",						},	// stage1 */
//	{	350,				(113) +((1)*21),	"2",						},	// stage2 */
//	{	340,				(113) +((2)*21),	"3",						},	// stage3 */
//	{	330,				(113) +((3)*21),	"4",						},	// stage4 */
//	{	320,				(113) +((4)*21),	"5",						},	// stage5 */
//	{	310,				(113) +((5)*21),	"6",						},	// stage6 */
//	{	275,				(113) +((6)*21),	"ENDING",					},	// ending */
//	{	0,0,NULL,	},//----------------
	{	GAME_X_OFFSET+(96), (115) +((0)*21),	"Unpause", 			},
	{	GAME_X_OFFSET+(96), (115) +((1)*21),	"Start Over", 		},
	{	GAME_X_OFFSET+(96), (115) +((2)*21),	"Quit Game",			},
	{	0,0,NULL,	},//----------------
	{	GAME_X_OFFSET+(144), (138) +((0)*21),	"Yes", 					},
	{	GAME_X_OFFSET+(146), (138) +((1)*21),	"No",					},
	{	0,0,NULL,	},//---------------- --------012345
	{	GAME_X_OFFSET+(32), (16),				"       tries left",	},
	{	GAME_X_OFFSET+(32), (48),				"If you continue,", 		},
	{	GAME_X_OFFSET+(32), (48+18),			"your score won't count",		},
	{	GAME_X_OFFSET+(32), (120),				"Do you want to continue?", 		},
	{	0,0,NULL,	},//----------------
};
/*---------------------------------------------------------
	コンティニューメニューの場合の見出し文字を描画
---------------------------------------------------------*/
static void render_continue(void)
{
		kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
		cg.msg_time = (65536);	/* 約 18 分 */
	{
		unsigned int yyy18;
		yyy18 = (3*18);/* Y位置 */
		unsigned int i;
		for (i=0; i<4; i++)
		{
			/* 4行目のみ特殊な位置へ移動。 */
			ml_font[(i+3)].x		= my_menu_resource[i+MENU_RESOURCES_14_TITLE01].x_offset;/* X位置 */
			ml_font[(i+3)].y		= my_menu_resource[i+MENU_RESOURCES_14_TITLE01].y_offset;/* Y位置 */
			ml_font[(i+3)].timer	= ML_ON;
			strcpy(my_font_text, my_menu_resource[i+MENU_RESOURCES_14_TITLE01].str_name );
			/* コンテニュー回数の表示 */
			if (0==i)
			{
				dec_print_format( ((cg.game_now_max_continue)), 2, (char *)&my_font_text[4]);
			}
			kanji_window_clear_line((i+3)); 	/* 漢字ウィンドウの4行目(==3)の内容を消す。 */
			set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18) ); /* カーソルを4行目(==3)へ移動 */
			kanji_color(7);/*(白色)*/
			kanji_draw();
			//
			yyy18 += (18);
		}
	}
}
/*---------------------------------------------------------

---------------------------------------------------------*/
static void stage_select_menu_draw_all(void)
{
	/* 描画 */
	psp_pop_screen();
	{
		unsigned int yyy18;
		yyy18 = (0);/* Y位置 */
		kanji_cursor_move_home_position();		/* 漢字カーソルをホームポジションへ移動 */
		cg.msg_time = (65536);	/* 約 18 分 */
		unsigned int i;
		for (i=0; i<aaa.max_items; i++)
		{
			unsigned int text_color;
			text_color = (7);/*(白色)*/
			//
			ml_font[i].x		= (aaa.menu_item_my_obj[i].offset_x);
			ml_font[i].y		= (aaa.menu_item_my_obj[i].offset_y);
			if (((signed)i)==aaa.selected_number)	/* 選択された */
			{
				text_color = (14);/*(黄色)*/
				ml_font[i].x += (2);	/* オフセットを 2[pixel] にする */
				ml_font[i].y += (2);	/* オフセットを 2[pixel] にする */
			}
			ml_font[i].timer	= ML_ON;
			//
			kanji_window_clear_line(i); 	/* 漢字ウィンドウのn行目(==0)の内容を消す。 */
			set_kanji_xy( (0), (yyy18) );
			strcpy(my_font_text, (char *)my_menu_resource[aaa.menu_offset+i].str_name);
			kanji_color(text_color);
			kanji_draw();
			//
			yyy18 += (18);
		}
	}
}


/*---------------------------------------------------------
	終了処理と移動処理。
---------------------------------------------------------*/

extern void gamecore_term(void);
extern void player_continue_value(void);
static void common_menu_work_MENU_STATE_03_FININSH(void)
{
//	SDL_SetAlpha(cb.sdl_screen[SDL_01_BACK_SCREEN], SDL_SRCALPHA, 255);
	psp_pop_screen();
	//
//	clear_kanji_line(); 	/* 漢字ウィンドウの位置を戻したり初期化したり。 */
//	set_kanji_hide_line(ML_LINE_02);/*(2行目以下を非表示にする。)*/ 	/*(ゲームモードの場合)*/
	set_kanji_hide_line(ML_LINE_04);/*(4行目以下を非表示にする。)*/ 	/*(シナリオモードの場合)*/
	kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	//
	if (MENU_TYPE_01_PAUSE==aaa.menu_type)
	{
		/* ボスデバッグ用 USE_r36_SCENE_FLAG */
		#if 0//1/*(1==DEBUG_MODE)*/
	//	if (psp_pad.pad_data & PSP_KEY_RIGHT)
		{
		//	cg_game_now_max_continue = (90);/*test*/	/* ランキングにさせない */
		//	cg.game_score	= (8);/*test*/
		//	cg.graze_point	= (0);/*test*/
		//	cg.zanki		= (8);/*test*/
		//	cg.bombs		= (8);/*test*/
		//	#if (0)
		//	/* ボスチェック用 */
		//	pd_weapon_power = MAX_POWER_IS_128;/*test*/
		//	#endif
			cg.game_score	= ((cg.state_flag>>8) & 0xff);/*(常に表示)*/
			cg.graze_point	= (cg.game_score);/*test*/
		}
		#endif
		#if 0//1/*(1==DEBUG_MODE)*/
	//	else
		if (psp_pad.pad_data & PSP_KEY_LEFT)
		{
			#if (1)//(USE_r36_SCENE_FLAG)
			NEXT_SCENE;
			#endif
		//	cg_game_now_max_continue = (90);/*test*/	/* ランキングにさせない */
			cg.game_score	= (0);/*test*/
		//	cg.graze_point	= (0);/*test*/
		//	cg.zanki		= (8);/*test*/
		//	cg.bombs		= (8);/*test*/
		//	#if (0)
		//	/* ボスチェック用 */
		//	pd_weapon_power = MAX_POWER_IS_128;/*test*/
		//	#endif
		}
		#endif
		if (/*MENU_ITEM_00_CONTINUE_GAME*/0 == aaa.selected_number)/* Continue Game */
		{
			#if 1/*(Gu化完了したら要らなくなる)*/
			{
				psp_clear_screen(); 	/* [PAUSE] 復帰時にSDL画面を消す。 */
			}
			/* SDLなのでこの機構が必要。Gu化完了したら要らなくなる */
			kaiwa_system_set_re_draw(); 	/* 会話システムにSDL再描画指示。 */
			#endif
			cb.main_call_func = cb.pause_out_call_func;
		}
		else
		if (/*MENU_ITEM_01_RETRY_GAME*/1 == aaa.selected_number)/* Retry Game */
		{
			gamecore_term();
		//	cg.msg_time = (0);/* 必要(?) */ 	/* 約 0 秒 */
			cb.main_call_func = stage_first_init;	/* 始めから */
		}
		else
	//	if (MENU_ITEM_02_QUIT_GAME == selected_number)/* Quit Game */
		{
			gamecore_term();
			cb.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
		}
	}
	else
	if (MENU_TYPE_02_ASK_CONTINUE==aaa.menu_type)
	{
		if (/*MENU_ITEM_00_CONTINUE_YES*/0 == aaa.selected_number)
		{
			/* Continue Game */
			player_continue_value();

			#if (1)//(USE_r36_SCENE_FLAG)
			/*(??????????????)*/
			//	  (cg.state_flag & 0x00008000u)//プレイヤーループを抜ける処理(とりあえず??????)
			cg.state_flag &= 0xffff7fffu;/*(とりあえず、現在仕様が良くわかんない)*/
			#endif

			#if 1/*(Gu化完了したら要らなくなる)*/
			{
				psp_clear_screen(); /* [PAUSE] 復帰時にSDL画面を消す。 */
			}
			#endif
			cb.main_call_func = shooting_game_core_work;
		}
		else
		{ /* Game over /Quit Game */
		//	gamecore_term();
		//	cb.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
			cb.main_call_func = gameover_start;
		}
	}
}


/*---------------------------------------------------------
	だんだん暗くする。暗くなったら次へ。
---------------------------------------------------------*/

static void common_menu_work_MENU_STATE_02_FADE_OUT(void)
{
	aaa.menu_brite -= FPS_MENU_FACTOR8;
	if (0 >= (aaa.menu_brite) )
	{
		aaa.menu_brite	= (0);
		cb.main_call_func = common_menu_work_MENU_STATE_03_FININSH; /* */
	}
	stage_select_menu_draw_all();
}
/*---------------------------------------------------------
	メニューキー入力受け付け。確定したら次へ。
---------------------------------------------------------*/

static void stage_select_menu_work_MENU_STATE_01_WORK_MENU(void)
{
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック(原作準拠) */
	{
		/*(上下を押した場合に操作音を出す。)*/
		if (psp_pad.pad_data & (PSP_KEY_DOWN|PSP_KEY_UP/*|PSP_KEY_PAUSE|PSP_KEY_SELECT*/))
		{
			voice_play_menu(VOICE02_MENU_SELECT, TRACK01_MENU01);
		}
		#if 0/*(-r34)*/
		/*(上下を押した場合、回り込み選択をする。上下は必ずワープ)*/
		if (psp_pad.pad_data & PSP_KEY_DOWN)
		{
			if (aaa.selected_number == aaa.max_items-1)
					{	aaa.selected_number = 0;	}
			else	{	aaa.selected_number++;		}
		}
		else
		if (psp_pad.pad_data & PSP_KEY_UP)
		{
			if (0 == aaa.selected_number)
					{	aaa.selected_number = aaa.max_items-1;	}
			else	{	aaa.selected_number--;		}
		}
		#else/*(r35-)*/
		/*(上下を押した場合、最大最小選択をする。メニュー上下は必ず停止)*/
		if (psp_pad.pad_data & PSP_KEY_DOWN)
		{	aaa.selected_number++;		aaa.selected_number = psp_min(aaa.selected_number, (aaa.max_items-1) ); 	}	/* メニュー下で停止 */
		else
		if (psp_pad.pad_data & PSP_KEY_UP)
		{	aaa.selected_number--;		aaa.selected_number = psp_max(aaa.selected_number, (0) );					}	/* メニュー上で停止 */
		#endif
		{ /* ショートカット機能 */
		//	if (MENU_TYPE_00_SELECT_STAGE==aaa.menu_type)
		//	{
		//	}
		//	else
//			if (MENU_TYPE_00_SELECT_STAGE!=aaa.menu_type)
		//	if (MENU_TYPE_01_PAUSE==aaa.menu_type)
		//	if (MENU_TYPE_02_ASK_CONTINUE==aaa.menu_type)
			{
				/* セレクトキーを押した場合、クイックリスタート。("始めから")  (原作のキーボードショートカット機能) */
				/* セレクトキーを押した場合、必ずコンティニューしない。 */
				if (psp_pad.pad_data & PSP_KEY_SELECT)					/* [select]ボタンで("始めから") */
			//	if (psp_pad.pad_data & PSP_KEY_SELECT)					/* [select]ボタンで必ずコンティニューしない */
				{
					aaa.selected_number 	= 1;//MENU_ITEM_01_RETRY_GAME;
				//	aaa.selected_number 	= 1;//MENU_ITEM_01_CONTINUE_NO;
					cb.main_call_func = common_menu_work_MENU_STATE_02_FADE_OUT;	/* メニュー消去準備 */
				}
				/* ポーズキーを押した場合、ポーズ解除。 */
				/* ポーズキーを押した場合、必ずコンティニュー決定。 */
				if (psp_pad.pad_data & PSP_KEY_PAUSE)				/* [start]ボタンでポーズ解除 */
			//	if (psp_pad.pad_data & PSP_KEY_PAUSE)				/* [start]ボタンで必ずコンティニュー決定 */
				{
					aaa.selected_number 	= 0;//MENU_ITEM_00_CONTINUE_GAME;
				//	aaa.selected_number 	= 0;//MENU_ITEM_00_CONTINUE_YES;
					cb.main_call_func = common_menu_work_MENU_STATE_02_FADE_OUT;	/* メニュー消去準備 */
				}

			}
		}
		if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
		{
			voice_play_menu(VOICE01_MENU_OK/*VOICE02_MENU_SELECT*/, TRACK01_MENU01);
			cb.main_call_func = common_menu_work_MENU_STATE_02_FADE_OUT;	/* メニュー消去準備 */
		}
	}
	stage_select_menu_draw_all();
}


/*---------------------------------------------------------
	だんだん明るくする。明るくなったら次へ。
---------------------------------------------------------*/

static void common_menu_work_MENU_STATE_00_FADE_IN_MENU(void)
{
	aaa.menu_brite += FPS_MENU_FACTOR8;
	if ((255) <= (aaa.menu_brite) )
	{
		aaa.menu_brite = (255);
		cb.main_call_func = stage_select_menu_work_MENU_STATE_01_WORK_MENU; /* */
	}
	stage_select_menu_draw_all();
}


/*---------------------------------------------------------
	共通メニュー初期化。
---------------------------------------------------------*/

static void common_menu_initialize(void)
{
	{
		/* 共通メニュー、ワークエリアの初期化 */
		unsigned int i;
		for (i=0; i<SPEC_08_MENU_ITEM_MAX; i++)
		{
			aaa.menu_item_my_obj[i].offset_x	= (0);
			aaa.menu_item_my_obj[i].offset_y	= (0);
		}
		// メニューに使用するサブ項目の数を調べる。
		{
			aaa.max_items		= (0);
			{
		loop:
				#if 0
				/* セレクトステージメニューの場合 */
				if (MENU_TYPE_00_SELECT_STAGE==aaa.menu_type)
				{
					/* 解放された部分まで。 */
					if (aaa.max_items>(option_config[OPTION_CONFIG_07_OPEN]&0x07))	{	goto loop_quit;}
				}
				#endif
				/* (終わりまで調べる) */
				/*while*/if (NULL == my_menu_resource[aaa.menu_offset+aaa.max_items].str_name)		{	goto loop_quit;}
				aaa.max_items++;
				goto loop;
		loop_quit:
				;
			}
		}
		// メニューに使用するサブ項目の文字。
		// オフセット位置を初期設定する。
		for (i=(0); i<(aaa.max_items); i++)
		{
			aaa.menu_item_my_obj[i].offset_x	= my_menu_resource[aaa.menu_offset+i].x_offset;
			aaa.menu_item_my_obj[i].offset_y	= my_menu_resource[aaa.menu_offset+i].y_offset;
		}
	//
		aaa.menu_brite			= (0);
	//	fade_out_flag	= (0)/*set_fade_out_flag*/;/*構造的問題*/
	}
		cg.msg_time = (65536);	/* 約 18 分 */
}

#if 0
/*---------------------------------------------------------
	ステージ選択メニューの開始処理。
	-------------------------------------------------------
---------------------------------------------------------*/
/*static*/global void stage_select_menu_start(void)
{
		psp_push_screen();
	{
		aaa.menu_type	= MENU_TYPE_00_SELECT_STAGE;
		aaa.menu_offset = MENU_RESOURCES_00_STAGE01;
		{
			#if 1
			/*
				エキストラステージをプレイした後で、
				「エキストラステージ、プラクティス」と
				「エンディング、スタッフロール、プラクティス」が
				選べるバグがあるので、修正する。
			*/
			if ((6-1) < cg.game_continue_stage) 	{cg.game_continue_stage = (6-1);	/* (6-1) */}
			#endif
			aaa.selected_number = cg.game_continue_stage;
		}
		common_menu_initialize();
		cb.main_call_func = common_menu_work_MENU_STATE_00_FADE_IN_MENU;
	}
}
#endif

/*---------------------------------------------------------
	ポーズメニューの開始処理。
	-------------------------------------------------------
	一時停止
	一時停止解除
	タイトルへ戻る
---------------------------------------------------------*/
extern void set_core_game_time_MAX(void);
/*static*/global MAIN_CALL_FUNC(pause_menu_start)
{
	{
		/*(ポーズメニューの場合の特殊処理)	*/
		if (
				(7==cg.game_now_stage)	/* スタッフロール1 */
			|| (10==cg.game_now_stage)	/* スタッフロール2 */
		)
		{
			set_core_game_time_MAX();
			cb.main_call_func = cb.pause_out_call_func;
			return;/*(強制的に戻る)*/
		}
	}
//	else
	{
		/*(ポーズメニューの場合はポースフィルターをかける)*/
		psp_pause_filter(); 	/* ポーズフィルター */
		psp_push_screen();
	//
		aaa.menu_type	= MENU_TYPE_01_PAUSE;
		aaa.menu_offset = MENU_RESOURCES_07_CONTINUE;
		aaa.selected_number 		= (0);// = MENU_ITEM_00_CONTINUE_GAME;/*"CONTINUE GAME"*/
		common_menu_initialize();
	//	fade_out_flag		= (0)/*set_fade_out_flag*/;/*構造的問題*/
	//	cb.main_call_func = pause_menu_local_workMENU_STATE_00_FADE_IN_MENU;
		cb.main_call_func = common_menu_work_MENU_STATE_00_FADE_IN_MENU;
	}
}


/*---------------------------------------------------------
	コンティニューするかい？メニューの開始処理。
	-------------------------------------------------------
---------------------------------------------------------*/

/*static*/global MAIN_CALL_FUNC(ask_continue_menu_start)
{
		render_continue();/*(コンティニューメニューの場合の見出し文字を描画)*/
	//
		/*(コンティニューメニューの場合はポースフィルターをかける)*/
		psp_pause_filter(); 	/* ポーズフィルター */
		psp_push_screen();
	{
		aaa.menu_type	= MENU_TYPE_02_ASK_CONTINUE;
		aaa.menu_offset = MENU_RESOURCES_11_YES;
		aaa.selected_number 		= (0);// = MENU_ITEM_00_CONTINUE_YES;/*"CONTINUE YES"*/
		common_menu_initialize();
	//	fade_out_flag		= (0)/*set_fade_out_flag*/;/*構造的問題*/
	//	cb.main_call_func = ask_continue_menu_00_FADE_IN_MENU;
		cb.main_call_func = common_menu_work_MENU_STATE_00_FADE_IN_MENU;
	}
}
