
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	ゲームオーバーの表示
	-------------------------------------------------------
	現在都合により game_over.c 内にある。
	Gu化が進めば独立する予定。
---------------------------------------------------------*/

/*---------------------------------------------------------
	以下
	-------------------------------------------------------
	RESULT表示(stage_clear.c)
	-------------------------------------------------------
	ゲームオーバーの表示(game_over.c)
	-------------------------------------------------------
	現在都合により score_panel.c 内にある。
	Gu化が進めば独立する予定。
---------------------------------------------------------*/

#include "kanji_system.h"

#include "kaiwa_sprite.h"

//extern void dec_print_format(unsigned int num, int size, char *my_str);



/*---------------------------------------------------------
	ゲームコア終了の後処理
---------------------------------------------------------*/

//extern void bg2_destroy(void);
extern void gu_set_bg_u32_clear_color(u32 set_u32_clear_color);
extern void do_kaiwa_system_terminate(void);
extern void kaiwa_obj_set_256(void);
global void gamecore_term(void)
{
	#if 1
	/*(会話モード終了処理)*/
	do_kaiwa_system_terminate();
	#else
	/*(do_kaiwa_system_terminate();と重複)*/
	ml_font[(0)].haikei 		= (ML_HAIKEI_m1_OFF);/* せりふ背景off */
	#endif
	kaiwa_obj_set_256();
	kaiwa_all_obj_draw_on_off(0);	/* 立ち絵を描画しない。 */
	//
	cg.bomber_time = (0);
	#if (1==USE_r36_SCENE_FLAG)
	/*(??????????????)*/
	/* off / 道中コマンド追加読み込み処理を停止する。 */
//	cg.state_flag		&= (~SCENE_NUMBER_MASK); 	/*(シーンを消す)*/
	cg.state_flag		&= (0xffff00ffu); 	/*(シーンを消す)*/
	cg.state_flag		|= (0x00008000u); //プレイヤーループを抜ける処理(とりあえず??????)
	#else
	/* 現在の version はボスを倒さないで抜けると Gu がまずいので対策 */
	cg.state_flag &= (~(STATE_FLAG_15_DRAW_BOSS_GAUGE));	/* Guは書かないとマズイ */
	#endif
	#if (1)
	cg.draw_boss_hp_value	= (0);/* よくわかんない */			/* Guは書かないとマズイ */
	#endif
//
	gu_set_bg_u32_clear_color(0xff000000);	/*AABBGGRR*/	/*(黒)*/
//	bg2_destroy();
	//sprite_controller_remove_all();
	/*
		この辺で boss とか core とか開放しなくていいんだっけ？
	*/
	obj_system_cleanup_all();/* [A00弾領域]と[A01固定敵領域]と[A02敵領域]と[A03固定領域]と[A04パネル領域]のOBJを全消去。 */
//	score_cleanup();
	set_music_volume(128);
}


/*---------------------------------------------------------
	RESULT表示
---------------------------------------------------------*/

static void render_stage_clear_result(void)
{
	/* 幽々子 特殊能力：ステージクリア時にボムが増える */
	if (YUYUKO==(cg_game_select_player))	/* 幽々子の場合 */
	{
		#if 1/*原作風*/
		if (3 > cg.bombs)	/* クリアー時にボムが３つ未満なら */
		{	cg.bombs = 3;	}	/* ３つに増やす */
		#endif
		#if 1/*模倣風*/
		if (8 > cg.bombs)	/* クリアー時にボムが９(8)つ未満なら */
		{	cg.bombs++; }	/* １つ増やす */
		#endif
		#if 0/*模倣風*/
		/*(MAXにする)*/
		cg.bombs = (8); 	/* ９(8)つに増やす (9個==8) */
		#endif
		/* ボムがなくてもクリアーすればボムが４つになる */
	}
//
	#if 0
	/* なんか知らんが、Lunaticでちょっとチェックしたら、オーバーフローするｗ。 */
	/* クリアボーナス チェック */
	player_dummy_add_score(adjust_score_by_difficulty((
//		(cg.game_now_stage	* score( 1000)) + /* ステージ x 1000 pts */ 	/* 原作風 */
//		(cg.weapon_power	* score(  100)) + /* パワー   x  100 pts */ 	/* 原作風 */
//		(cg.graze_point)					  /* グレイズ x   10 pts */ 	/* 原作風 */
//
		(cg.game_now_stage	* score(10000)) + /* ステージ x 10000 pts */	/* 模倣風 */
		(cg.graze_point 	* score( 1000)) + /* グレイズ x  1000 pts */	/* 模倣風 */
		(cg.weapon_power	* score(  100)) /* パワー	  x   100 pts */	/* 模倣風 */
	)));
	#else
	/* なんか知らんが、オーバーフローするので、個別に足してみる。 */
	/* クリアボーナス チェック */
	player_dummy_add_score(adjust_score_by_difficulty(( (((u32)cg.game_now_stage)	* score(10000)) 	)));	/* ステージ x 10000 pts */	/* 模倣風 */
	player_dummy_add_score(adjust_score_by_difficulty(( (((u32)cg.graze_point)		* score( 1000)) 	)));	/* グレイズ x  1000 pts */	/* 模倣風 */
	player_dummy_add_score(adjust_score_by_difficulty(( (((u32)cg.weapon_power) 	* score(  100)) 	)));	/* パワー	x	100 pts */	/* 模倣風 */
	#endif
//
	{
		//					 "012345678901234567890"
		strcpy(my_font_text, "Result" );
		//
		ml_font[ML_LINE_01].x		= ( 40);
		ml_font[ML_LINE_01].y		= ( 32);
		ml_font[ML_LINE_01].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_01);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_01*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color((7)/*|STR_CODE_NO_ENTER*/);
		kanji_draw();
	}
//	strcpy(my_font_text, "Stage   0 x 1000 pts."); /* 原作風 */
//	strcpy(my_font_text, "Power 000 x  100 pts."); /* 原作風 */
//	strcpy(my_font_text, "Graze 000 x   10 pts."); /* 原作風 */
	/* 模倣風 */
	{
		//					 "012345678901234567890"
	//	strcpy(my_font_text, "Stage   0 x 10000 pts.");
		strcpy(my_font_text, "Stage   0 x 10000 pts.");
		dec_print_format( cg.game_now_stage, 1, (char *)&my_font_text[ 8]);
		//
		ml_font[ML_LINE_02].x		= ( 48);
		ml_font[ML_LINE_02].y		= ( 60);
		ml_font[ML_LINE_02].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_02);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_02*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color(9);
		kanji_draw();
	}
	{
		//					 "012345678901234567890"
	//	strcpy(my_font_text, "Graze0000 x  1000 pts.");
		strcpy(my_font_text, "Graze   0 x  1000 pts.");
		dec_print_format( cg.graze_point,	 4, (char *)&my_font_text[ 5]);
		//
		ml_font[ML_LINE_03].x		= (  48);
		ml_font[ML_LINE_03].y		= (  80);
		ml_font[ML_LINE_03].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_03);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_03*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color(9);
		kanji_draw();
	}
	{
		//					 "012345678901234567890"
	//	strcpy(my_font_text, "Power 000 x   100 pts.");
		strcpy(my_font_text, "Power   0 x   100 pts.");
		dec_print_format( cg.weapon_power,	 3, (char *)&my_font_text[ 6]);
		//
		ml_font[ML_LINE_04].x		= (  48);
		ml_font[ML_LINE_04].y		= ( 100);
		ml_font[ML_LINE_04].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_04);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_04*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color(9);
		kanji_draw();
	}
	cg.graze_point = 0;/* 清算して消える */
	const char *level_name[4] =
	{
	//	"Easy      x 0.5",	/* 原作風 */
	//	"Normal    x 1.0",	/* 原作風 */
	//	"Hard      x 1.2",	/* 原作風 */
	//	"Lunatic   x 1.5",	/* 原作風 */
		"Easy      x 0.5",	/* 模倣風 */
		"Normal    x 1.0",	/* 模倣風 */
		"Hard      x 2.0",	/* 模倣風 */
		"Lunatic   x 5.0",	/* 模倣風 */
	};
	{
		strcpy(my_font_text, (char *)level_name[((cg.game_difficulty)/*&0x03*/)]);
		//
		ml_font[ML_LINE_05].x		= ( 40);
		ml_font[ML_LINE_05].y		= (160);
		ml_font[ML_LINE_05].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_05);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_05*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color(7);
		kanji_draw();
	}
//
	#if 0/* ボス倒した場合の処理にいれた */
	pd_bomber_time = 0;/* 都合上 */
	set_bg_alpha(255);/* 画面を明るくする */
	#endif
//	/* ステージクリア チェック */
	/* PRACTICE 開放 チェック */
	if ((option_config[OPTION_CONFIG_07_OPEN] & (0x07)) < (cg.game_now_stage&0x07))
	{
		/* PRACTICE 開放 (進んだステージを練習可能にする) */
		option_config[OPTION_CONFIG_07_OPEN] &= (~0x07);
		option_config[OPTION_CONFIG_07_OPEN] |= (cg.game_now_stage&0x07);
	}
	cg.msg_time = (65536);	/* 約 18 分 */
}


/*---------------------------------------------------------
	GAME_OVER表示
---------------------------------------------------------*/

typedef struct
{
	int xxx;
	int yyy;
	const char *sss1;
	int color1;
	const char *sss2;
	int color2;
} GMENU_TEST;

static GMENU_TEST result_my_obj[8] =
{	//																			"00000000001"
//																				"01234567890"
	{	32+(64),	( 32),	"Your skill", 		((15)|STR_CODE_NO_ENTER),	"", 			((7)|STR_CODE_NO_ENTER) },//"PLAYER DATA"/*"GAME OVER"*/
	{	32+(48),	( 60),	"Final score          ",	((6)|STR_CODE_NO_ENTER),	"0000000000.",	((7)|STR_CODE_NO_ENTER) },
	{	32+(48),	( 80),	"Number of mistakes          ",	((5)|STR_CODE_NO_ENTER),	"         0.",	((7)|STR_CODE_NO_ENTER) },	/* 集計システム(player_data)総ミス回数 */
	{	32+(48),	(100),	"Bomb usage count      ",	((4)|STR_CODE_NO_ENTER),	"         0.",	((7)|STR_CODE_NO_ENTER) },	/* 集計システム(player_data)総ボム使用回数 */
	{	32+(48),	(120),	"Number of successful bombs",	((3)|STR_CODE_NO_ENTER),	"         0.",	((7)|STR_CODE_NO_ENTER) },	/* 集計システム(player_data)総喰らいボム成功回数 */
	{	32+(48),	(140),	"Number of continuations",	((2)|STR_CODE_NO_ENTER),	"         0.",	((7)|STR_CODE_NO_ENTER) },	/* 集計システム(player_data)総コンティニュー回数 */
	{	32+(48),	(160),	"Difficulty            ",	((1)|STR_CODE_NO_ENTER),	"   Lunatic.",	((7)|STR_CODE_NO_ENTER) },
};

static void render_game_over_result(void)
{
	const char *level_name[4] =
	{
		"      Easy.",
		"    Normal.",
		"      Hard.",
		"   Lunatic.",
	};
	cg.player_data_use_continue--;	/* 集計システム(player_data)_ (現プログラムの都合上)コンティニュー回数0で 1回カウントされるので、その分減らして辻褄あわせをする。 */
//
	unsigned int yyy18;
	yyy18 = 0;
	unsigned int i;
	for (i=0; i<7; i++)//ML_LINE_01 ... ML_LINE_07
	{
		ml_font[i].x		= result_my_obj[i].xxx;
		ml_font[i].y		= result_my_obj[i].yyy;
		ml_font[i].timer	= ML_ON;
		kanji_window_clear_line(i); /* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (yyy18) ); /* カーソルを1行目(==0)へ移動 */
		//
		kanji_color((result_my_obj[i].color1));
		strcpy(my_font_text, &result_my_obj[i].sss1[0]	 );
		kanji_draw();
		//
		kanji_color((result_my_obj[i].color2));
		strcpy(my_font_text, &result_my_obj[i].sss2[0]	 );
		//
		void *aaa[(8)] =
		{
			&&bbb7, 		&&bbb1, 		&&bbb2, 		&&bbb3,
			&&bbb4, 		&&bbb5, 		&&bbb6, 		&&bbb7,
		};
		goto *aaa[(i)];
	bbb1:	dec_print_format( cg.game_score,					9, (char *)&my_font_text[0]);		goto bbb7;
	bbb2:	dec_print_format( cg.player_data_count_miss,		3, (char *)&my_font_text[7]);		goto bbb7;
	bbb3:	dec_print_format( cg.player_data_used_bomber,		3, (char *)&my_font_text[7]);		goto bbb7;
	bbb4:	dec_print_format( cg.player_data_use_kurai_bomb,	3, (char *)&my_font_text[7]);		goto bbb7;
	bbb5:	dec_print_format( cg.player_data_use_continue,		3, (char *)&my_font_text[7]);		goto bbb7;
	bbb6:	strcpy(my_font_text, (char *)level_name[((cg.game_difficulty)/*&0x03*/)]);				goto bbb7;
	bbb7:
		kanji_draw();
		yyy18 += (18);
	}
	cg.msg_time = (65536);	/* 約 18 分 */
}
/* counter bomb defensive revival. */


/*---------------------------------------------------------
	うーん、Gu化中なので、ちゃんと機能しない。
	(SDL画面のみに対するエフェクト)
---------------------------------------------------------*/
static void effect_dark_screen(void)
{
#if 0
	#if 1
	/* KETM互換なら ここで back buffer screen を clear screen すべき */
	psp_push_screen();
	#endif
	SDL_SetAlpha(sdl_screen[SDL_00_VIEW_SCREEN],SDL_SRCALPHA,128);
	psp_push_screen();
	SDL_SetAlpha(sdl_screen[SDL_00_VIEW_SCREEN],SDL_SRCALPHA,255);
#endif
}


/*---------------------------------------------------------
	RESULT表示(ゲーム各面クリアー時)
---------------------------------------------------------*/

extern void player_loop_quit(void);

static int result_time_out;
/* 曲がフェードアウトする時間は強制的に待つ */
#define MUSIC_SKIP_TIME 	byou60(5)	/* 約 5 秒(ボタンで飛ばせる時間) */
#define MUSIC_FADE_OUT_TIME byou60(4)	/* 約 4 秒(飛ばせない時間) */

static MAIN_CALL_FUNC(stage_clear_result_screen_local_work)
{
	result_time_out--;
	/* ボタンで飛ばせる時間ならキーチェック */
	if (MUSIC_FADE_OUT_TIME < result_time_out)
	{
		if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック */
		{
			if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT|PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL|PSP_KEY_SLOW|PSP_KEY_OPTION))
			{
				result_time_out = (MUSIC_FADE_OUT_TIME+1);
			}
		}
	}
	else
	/* 飛ばせない時間になったら、少女祈祷中を表示。曲(BGM)をフェードアウト開始。 */
	if (MUSIC_FADE_OUT_TIME == result_time_out) 	/* */
	{
	//	cg.msg_time = byou60(5);	/* 約 5 秒 */
		cg.msg_time = (65536);	/* 約 18 分 */
		{
		strcpy(my_font_text, "CHALLENGE NEXT STAGE!　Teenage girl praying..." );
		//
		ml_font[ML_LINE_08].x		= (40);
		ml_font[ML_LINE_08].y		= (230);
		ml_font[ML_LINE_08].timer	= ML_ON;
		kanji_window_clear_line(ML_LINE_08);	/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
		set_kanji_xy((0)*(KANJI_FONT_08_HARF_WIDTH), (ML_LINE_08*18) ); /* カーソルを1行目(==0)へ移動 */
		kanji_color(7);
		kanji_draw();
		}
	}
	else
	if (0 == result_time_out)	/* おしまい */
	{
		#if (1)/* 曲のフェードアウト作ったら要らなくなる。 */
		play_music_num(BGM_00_stop);
		set_music_volume(127/*SDL_MAXVOLUME*/);/* たぶん */
		#endif
		#if (1==USE_r36_SCENE_FLAG)
		/*(??????????????)*/
		if (cg.state_flag & 0x00008000u)//プレイヤーループを抜ける処理(とりあえず??????)
		/* 会話システムで終了指示されたら、終了する */
		#endif
		{
		//	#if 1/* この２つのセットで自動的に終了(GAME OVER)する */
		//	cg_game_now_max_continue = 1;	/* コンティニューさせない */
		//	player_loop_quit();
		//	#endif
			#if (0)
			psp_clear_screen();
			psp_push_screen();
			#endif
			cg.game_now_stage--;/* 7までしか無いので */
			cb.main_call_func = gameover_start;
//			if (0x7f==can_player_bit)
//			{
//				can_player_bit = 0xff;	/* チルノ Q 開放 */
//			}
		}
		else		/* 通常時。(ファンタズムの場合もこちら、ファンタズムendへ) */
		{
			cb.main_call_func = common_load_init;
		}
	}
	else
	{
		/* 曲のフェードアウト処理 */
		if (127 > result_time_out)/* SDL mixerの仕様(0-126で指定) */
		{
			set_music_volume(result_time_out);
		}
	}
}


/*---------------------------------------------------------
	RESULT表示(ゲーム各面クリアー時)の処理開始
---------------------------------------------------------*/

global MAIN_CALL_FUNC(stage_clear_result_screen_start)
{
	kanji_window_all_clear();				/* 漢字画面を全行消す。漢字カーソルをホームポジションへ移動。 */
	render_stage_clear_result();
	effect_dark_screen();
	result_time_out 	= MUSIC_FADE_OUT_TIME + MUSIC_SKIP_TIME;	/* (約 4 秒)+(約 5 秒) */
	cb.main_call_func = stage_clear_result_screen_local_work;
}

/*---------------------------------------------------------
	ゲームオーバーの場合

---------------------------------------------------------*/

static int game_over_time_out;/*wait*/

static MAIN_CALL_FUNC(gameover_local_work)
{
//	psp_pop_screen();
	if (0==psp_pad.pad_data_alter)/* さっき何も押されてなかった場合にキーチェック */
	{
		if (psp_pad.pad_data & (PSP_KEY_LEFT|PSP_KEY_RIGHT|PSP_KEY_UP|PSP_KEY_DOWN|PSP_KEY_SHOT_OK|PSP_KEY_BOMB_CANCEL|PSP_KEY_SLOW|PSP_KEY_OPTION))
		{
			game_over_time_out = (0);
		}
	}
	game_over_time_out--;
	if (0 > game_over_time_out)
	{
		/*(r39)*/cg.side_panel_draw_flag = (0);/*(Gu描画: 右サイドのスコアパネル表示を非表示にする。でないと名前入力画面がおかしくなる)*/
		if (
			#if (0==USE_CONTINUED_RANKING)
		//	( (/*3*/DEFAULT_MAX_CONTINUE-1) == cg.game_now_max_continue ) &&
			( 0 == cg.player_data_use_continue ) && 							/* ノーコンティニューの場合のみスコアランキング */
			#endif
			(cg.game_score > high_score_table[(cg_game_select_player)][4].score)
		)
		{
			/* 最終スコアがランクインしてた場合 */
			cb.main_call_func = name_entry_start;	/* 名前入力画面へ */
		}
		else	/* タイトル画面へ */
		{
			/* 最終スコアがランクインしてない場合 */
			cg.game_now_stage = (0);/*要る？*/
			cb.main_call_func = title_menu_start;	/* タイトルメニューへ移動 */
		}
	}
}

/*---------------------------------------------------------
	ゲームオーバーの処理開始
---------------------------------------------------------*/

global MAIN_CALL_FUNC(gameover_start)/* init */
{
	/* 初期化 */
	//void gameover_init(void)
	render_game_over_result();/* gamecore_term();より前の必要がある。 */
	gamecore_term();
	effect_dark_screen();
	game_over_time_out = byou60(60);	/* 約 1 分 */
	cb.main_call_func = gameover_local_work;
}
