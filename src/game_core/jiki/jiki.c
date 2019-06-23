
#include "game_main.h"

/*---------------------------------------------------------
	東方模倣風 ～ Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	各プレイヤー
	REIMU(A/B) MARISA(A/B/C) REMILIA CIRNO YUYUKO
	-------------------------------------------------------
	博麗 霊夢 A (霊符)					(はくれい れいむ)
	博麗 霊夢 B (夢符)					(はくれい れいむ)
	霧雨 魔理沙 A (魔符)				(きりさめ まりさ)
	霧雨 魔理沙 B (恋符)				(きりさめ まりさ)
	レミリア スカーレット				(Remilia Scarlet)
	華胥の亡霊			西行寺 幽々子	(さいぎょうじ ゆゆこ)
	幽冥楼閣の亡霊少女	西行寺 幽々子	(さいぎょうじ ゆゆこ)
	チルノ A (氷符) 					(Cirno)
	チルノ ⑨ (⑨符)					(Cirno)
---------------------------------------------------------*/

#include "jiki_local.h"
#include "kanji_system.h"

#include "../menu/kaiwa_sprite.h"

/*---------------------------------------------------------

---------------------------------------------------------*/

#if 1/* たぶんこの位置で。 */
//global   signed int cg.game_difficulty;	/* GAME_CORE_GLOBAL_CLASSに、意図的に入れないもの */
global unsigned int cg_game_select_player;	/* GAME_CORE_GLOBAL_CLASSに、意図的に入れないもの */
global GAME_CORE_GLOBAL_CLASS __attribute__((aligned(32))) cg;
#endif



/*---------------------------------------------------------
	カード発動時の立ち絵
---------------------------------------------------------*/
#if 0
static OBJ_CALL_FUNC(player_move_tachie)
{
	if ((128-1) < cg.bomber_time)/* 残り時間が 128 以上なら、移動して待機 */
	{
		/* 画面外から出現、停止。しばし待つ。 */
		if (t256(100) > src->center.x256)
		{
			src->center.x256 += t256(5.0);
		}
	}
	else
	if ((1/*-1 */) < cg.bomber_time)/* 拡大 */
	{
		/* (24+(1))  、ここでの cg.bomber_time は、最大0x7fなので。 */
		src->color32		= (cg.bomber_time<<(24+(1)))|0x00ffffff;
		src->m_zoom.x256	+= (10);
		src->m_zoom.y256	+= (10);
	}
	else
	{
		src->jyumyou = JYUMYOU_NASI;	/* 時間制限でおしまい */
	}
}
#else
static int aaa_wait;
static OBJ_CALL_FUNC(player_move_tachie)
{
	// ボス(立ち絵移動)
	#if 0/*(等速移動)*/
	kaiwa_sprite[0].center.y256 	= t256(272+128) - ((aaa_wait)<<9);
	#else/*(加減速移動)*/
	{
		u32 aaa = (aaa_wait)+(aaa_wait);
		aaa += 128;/*(上下入れ替え)*/
		aaa &= 0xff;/*(0...255)*/
	//	aaa = ((aaa)|(aaa<<8));/*(0...65535)*/
		aaa <<= 8;/*(0...65535)*/
		aaa = vfpu_ease_in_out65536(aaa);
		aaa += 32768;/*(上下入れ替え)*/
		aaa &= 0xffff;/*(0...65535)*/
		aaa += aaa;/*(2倍)*/
	//	kaiwa_sprite[0].center.y256 	= t256(272+128) - (aaa);/*(上から下[ボス])*/
		kaiwa_sprite[0].center.y256 	= (aaa) - t256(256);/*(下から上[プレイヤー])*/
	}
	#endif
	aaa_wait--; /* ボス行動 */
	if (0 > aaa_wait)
	{
		src->jyumyou = JYUMYOU_NASI;	/* 時間制限でおしまい */
	}
}
#endif

/* -------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------- */

/*
	cg.jiki_weapon_level_offset == player番号 + (武器レベル x 8)
	cg.jiki_weapon_level_offset =  (cg_game_select_player) + (weapon_level<<3);
 */

/*---------------------------------------------------------
	プレイヤー立ち絵生成
	(幽々子)[幽々子ボムの扇本体]
---------------------------------------------------------*/

static void player_create_bomber_tachie(void/* OBJ *src */)
{
	OBJ *h;
	h					= obj_regist_teki();
	if (NULL!=h)/* 登録できた場合のみ */	/* (?) */
	{
		h->m_Hit256R			= JIKI_ATARI_ITEM_80;
		h->callback_mover		= player_move_tachie;
	#if 0
		h->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xff);
		/* 立ち絵初期位置 */
		h->center.x256				= -t256(150);	// (200)	/* 0 */  /* (src->center.x256) */
		h->center.y256				=  t256(150);	// (100)	/* GAME_HEIGHT+1 */ /* (src->center.y256) */
		h->obj_type_set 		= (JIKI_BOMBER_00); 	/* OBJ_Z01_JIKI_GET_ITEM */ /* JI KI_SHOT_00 */ /* ボスの直接攻撃は禁止 */
	#else
		h->obj_type_set 		= (JIKI_OPTION_01_00);/*  ダミー */
	//	kaiwa_sprite[0].center.x256 	= t256(256);
		kaiwa_sprite[0].center.x256 	= t256(32);
		aaa_wait				= (127);/*on*/
	#endif
		/* 描画用角度 */
		h->rotationCCW1024		= (0);//(256);
	/* ??? */h->kougeki_ti		= (0); /* 立ち絵なので強さ0. */ 	/*1  8*1 */
	}
}


enum
{
	//...
	LIMIT_m64_MINUS_LIMIT		= (-64),// LIMIT_m64_MINUS_LIMIT		= (-255),
	LIMIT_fukki2				= (-48),// 復帰2 < LIMIT_fukki2
	LIMIT_m127_MIN				= (-32),// 復帰1 < LIMIT_m127_MIN		= (-127),
	LIMIT_m16_GAME_OUT			= (-16),
	LIMIT_m1_KURAI_BOMB_UKETUKE = (-1),
	LIMIT_0_ZERO				= (0),
	LIMIT_1_ONE 				= (1),
//	LIMIT_128					= (128),
//	LIMIT_256					= (256),
	LIMIT_300_CONTINUE			= (300),	/* 約5[秒]		コンティニューした場合の復帰時間		5.00[秒] == 300 / 60. */
	LIMIT_512_STAGE_START		= (512),	/* 約8.53[秒]	ステージ開始時の無敵時間(特別に長い)	8.53[秒] == 512 / 60. */
	LIMIT_65535_BOSS_TAOSITA				= (65535),	/* 約18.2[分]	ボス倒した場合の無敵時間(特別に超長い)	18.2[分] == 65535 / 60 / 60. */
};

/* 0==特殊イベント発生していない。 */
static signed int pds_status_timer; /* 特殊イベント発生中タイマー */
//static int cg.special_ivent_type; /* 特殊イベントの種類 */


/*---------------------------------------------------------
	プレイヤー弾(ショット/針兼用)生成、子関数
	プレイヤー、針弾(霊夢)の追加
		(霊夢)		[針弾]、
		(魔理沙)	[森弾]、
		(レミリア)	[コウモリ弾]、
		(幽々子)	[蝶弾] 、
		(仮チルノ)	[丸氷弾]、
---------------------------------------------------------*/

extern OBJ_CALL_FUNC(reimu_yuyuko_create_bomber_kekkai_parrent);		/* 霊夢専用 ボムの親 */
//extern OBJ_CALL_FUNC(yuyuko_create_bomber_gyastry_dream_parrent); 	/* 幽々子専用 */
#define yuyuko_create_bomber_gyastry_dream_parrent reimu_yuyuko_create_bomber_kekkai_parrent

extern OBJ_CALL_FUNC(marisa_create_bomber_master_spark_parrent);		/* 魔理沙 B専用 ボムの親 */
extern OBJ_CALL_FUNC(chrno_q_create_bomber_gyastry_dream_parrent);		/* チルノ⑨専用 */
extern OBJ_CALL_FUNC(marisa_create_bomber_star_dust_levarie_parrent);	/* 魔理沙 A専用 低速ボムの親 */
extern OBJ_CALL_FUNC(remilia_create_bomber_cross_shot_parrent); 		/* レミリアボムの親 */
extern OBJ_CALL_FUNC(yuyuko_create_bomber_meifu_parrent);				/* 幽々子専用 低速ボムの親 */
extern OBJ_CALL_FUNC(marisa_create_bomber_homing_parrent);				/* 低速ボムの親 */
extern OBJ_CALL_FUNC(reimu_create_bomber_homing_shot_parrent);			/* 霊夢専用 低速ボムの親 */
/*---------------------------------------------------------
	プレイヤーキー操作
---------------------------------------------------------*/

extern void set_bg_alpha(int set_bg_alpha);
extern void register_main_shot(OBJ *s1);

extern int jiki_shot_get_player_animation_speed(void);/* プレイヤーのアニメーション速度を設定 */
extern void jiki_shot_oya_hide(void);/*(自機ショットの親を非表示にする。)*/

//enum /* _player_state_ */
//{
//	PLAYER_STATE_00_NORMAL,
//	PLAYER_STATE_01_KURAI_BOMB_UKETUKE,
//	PLAYER_STATE_02_SAVE_01,
//	PLAYER_STATE_03_SAVE_02,
//	PLAYER_STATE_04_GAME_OUT,
//};
extern void jiki_shot_set_bomber_time(void);/*(プレイヤー。 ボムの寿命を設定)*/
static void player_keycontrol(OBJ *s1)
{
	/*---------------------------------------------------------
		プレイヤーボム関連処理
	---------------------------------------------------------*/
//	if (STATE_FLAG_0x0200_IS_KAIWA_MODE==(cg.state_flag & STATE_FLAG_0x0200_IS_KAIWA_MODE))
//	{
//		;	/* 会話イベント中はボム関連の処理はしない */
//	}
//	else
	/*(ボンバー有効期間中)*/
	if (0 < cg.bomber_time) 	/* ボムウェイト処理 */
	{
		/* シナリオ時にも自機ボンバー時間経過する。(現在my_special()で自機ボム終了しないとシナリオ読まない仕様の為) */
		cg.bomber_time--; /*fps_factor*/
		if (2 > cg.bomber_time)
		{
			set_bg_alpha(255);/* 画面を明るくする */
			jiki_shot_oya_hide();/*(自機ショットの親を非表示にする。)*/
	//	}
	//	else
	//	if (190 > cg.bomber_time)
	//	{
			cg.state_flag &= (~JIKI_FLAG_0x0020_BOMBER_SYUU_SYUU);	/* ボムによる自動収集は終わり */
		}
	}
	/*(ボンバー無効期間中)*/
	else
//	if (0 >= cg.bomber_time)
	{
		cg.bomber_time = 0;
		/* シナリオ時には誘導弾を追加しない */
		if (IS_SCENE_KAIWA_TATAKAU)
		{
			if (psp_pad.pad_data & PSP_KEY_BOMB_CANCEL)
			{
				if (0 < cg.bombs)/*(残ボンバーがある場合)*/
				{
					cg.bombs--;
					cg.player_data_used_bomber++;	/* 集計システム(player_data)ボム使用回数 */
					cg.state_flag	|= JIKI_FLAG_0x0020_BOMBER_SYUU_SYUU; /*(ボムによる自動収集可能)*/
					voice_play_menu(VOICE07_BOMB, TRACK02_JIKI_BOMBER);/*("自機ボム"用トラック)*/
					set_bg_alpha(50);/* (100);(127);画面を暗くする */
					/* 立ち絵 */
					player_create_bomber_tachie(/* obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER] */);
					//
					//
					static /* const */ void (*regist_call_table[(PLAYERS8*2)])(OBJ/**/ *src) =/* 16 */
					{
						reimu_create_bomber_homing_shot_parrent,				reimu_yuyuko_create_bomber_kekkai_parrent,	/* 霊夢 A */
						reimu_yuyuko_create_bomber_kekkai_parrent,				marisa_create_bomber_homing_parrent,		/* 霊夢 B */
						marisa_create_bomber_star_dust_levarie_parrent, 		marisa_create_bomber_homing_parrent,		/* 魔理沙 A */
						marisa_create_bomber_master_spark_parrent,				marisa_create_bomber_homing_parrent,		/* 魔理沙 B */
						remilia_create_bomber_cross_shot_parrent,				marisa_create_bomber_homing_parrent,		/* レミリア */
						yuyuko_create_bomber_gyastry_dream_parrent, 			yuyuko_create_bomber_meifu_parrent, 		/* 幽々子 */
						marisa_create_bomber_star_dust_levarie_parrent, 		reimu_create_bomber_homing_shot_parrent,	/* チルノ A */
						chrno_q_create_bomber_gyastry_dream_parrent,			marisa_create_bomber_homing_parrent,		/* チルノ Q */
					};
						int index_aaa;
						index_aaa = (((cg_game_select_player))+((cg_game_select_player))+((psp_pad.pad_data & PSP_KEY_SLOW)?1:0));
					{
						(regist_call_table[(index_aaa)])(&obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER]);
					}
					s1->color32 				= MAKE32RGBA(0xff, 0xff, 0xff, 0x50);	/* 半透明 */
					{
						OBJ *zzz_obj_maru;
						zzz_obj_maru = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
						zzz_obj_maru->color32	= MAKE32RGBA(0xff, 0x88, 0x88, 0x50);	/* 半透明 */
					}
//					if (PLAYER_STATE_01_KURAI_BOMB_UKETUKE==cg.special_ivent_type)/* 喰らいボム受付中 */
					if (LIMIT_0_ZERO > pds_status_timer)/* 喰らいボム受付中 */
					{
						cg.player_data_use_kurai_bomb++;/* 集計システム(player_data)喰らいボム成功 */
					}
//					pds_status_timer = LIMIT_128;// cg.special_ivent_type	= PLAYER_STATE_03_SAVE_02;
					/* cg.bomber_time と ->jyumyouで同時に動作 */
					jiki_shot_set_bomber_time();
					//	#define USER_BOMOUT_WAIT (30)
					pds_status_timer	= cg.bomber_time + USER_BOMOUT_WAIT;/* 実質無敵時間 */
					/*	実質無敵時間 == (設定無敵時間 + USER_BOMOUT_WAIT)。 	実質無敵時間 == 設定無敵時間 だと、わかりにくいので若干の余裕が必要。 */
				//
					kanji_window_clear_line(0); 			/* 漢字ウィンドウの1行目(==0)の内容を消す。 */
					kanji_cursor_move_home_position();		/* カーソルを1行目(==0)へ移動 */
					{
						ml_font[(0)].haikei 		= (ML_HAIKEI_02_JIKI_SPELL_CARD);/* [赤/自機カード用背景]せりふ背景on */
						cg.msg_time 				= cg.bomber_time;	/* byou60(5) */ /* 約 5 秒 */
						typedef struct
						{
							const char *spell_str_name; 	/* カード名称 */
						} aaa_RESOURCE;
						static const aaa_RESOURCE my_aaa_resource[(PLAYERS8*2)] =
						{
//	 "feeddccbbaa99887766554433221100",'\0' 	 "feeddccbbaa99887766554433221100",'\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{"Fantasy Seal" 				"\n"},	{"Homing Amulet" 				"\n"},//霊符「夢想結界・円」
	{"Persuation Needle" 				"\n"},	{"Evil Sealing Circle" 				"\n"},//夢符「夢想結界・斬」
	{"Stardust Reverie"	"\n"},	{"Magic Missile"				"\n"},
	{"Illusion Laser" 		"\n"},	{"Master Spark"				"\n"},
	{"Night Dance"			"\n"},	{"Bombard Night" 			"\n"},
	{"Spirit Sign"		"\n"},	{"Ageless Dream" 				"\n"},// うつつ、「現」、「打棄つ」。「現」実の。打ち「捨てる」。 /* dream cast. ghastly dream(妖々夢). ghastly dream(霊夢). */
	{"Ice Sign" 	"\n"},	{"Icicle Fall" 			"\n"},	/* 霰(あられ): 雨が凍ったり、溶けかけた雪が再び凍って降る。 */
	{"★Ice Sign"				"\n"},	{"Frozen Sword+99999"				"\n"},	/* 霙符 霜踏 霙(みぞれ): 雨と雪が混ざって降る。 */
						};
						strcpy(my_font_text, my_aaa_resource[index_aaa].spell_str_name);
						kanji_color((7)|STR_CODE_NO_ENTER);
						kanji_draw();
					}
				}
			}
		}
	}

//
//	if (PLAYER_STATE_01_KURAI_BOMB_UKETUKE==cg.special_ivent_type) return;/* 喰らいボム受付中 */
	if (LIMIT_0_ZERO > pds_status_timer)	{	return; 	}	/* 喰らいボム受付中 */
//
	/*---------------------------------------------------------
		プレイヤー移動関連処理
	---------------------------------------------------------*/
	#if (0)
	/*
		紅魔郷
		妖々夢
		永夜抄
		花映塚
		文花帖
		風神録0.02a
	*/
	static const s16 jiki_move_length[16][2] =
	{
	/* LDRU */ /* y x */
	// 斜め移動が速いのが正しいのを修正。
	/* 0000 */ {	  0,	0},
	/* 0001 */ {	  0, -256},/* 0 U */
	/* 0010 */ {	256,	0},/* 2 R */
	/* 0011 */ {	256, -256},/* 1 UR */
	/* 0100 */ {	  0,  256},/* 4 D */
	/* 0101 */ {	  0,	0},
	/* 0110 */ {	256,  256},/* 3 DR */
	/* 0111 */ {	  0,	0},
	/* 1000 */ {   -256,	0},/* 6 L */
	/* 1001 */ {   -256, -256},/* 7 UL */
	/* 1010 */ {	  0,	0},
	/* 1011 */ {	  0,	0},
	/* 1100 */ {   -256,  256},/* 5 DL */
	/* 1101 */ {	  0,	0},
	/* 1110 */ {	  0,	0},
	/* 1111 */ {	  0,	0},
	};
	/* 斜め移動は 風神録0.02a までは 考慮しない。 */
	/*
		紅魔郷 から 風神録0.02a までは、斜め移動が速い。
		模倣風は、これらの場所が多いので、準拠するなら本来斜め移動を速くするべき。
		しかし、pspの画面は小さい為、斜め移動が速いのが目立つ。
		斜め移動が速いとかえってバランスが崩れるので、模倣風では斜め移動を遅くする。(距離に合わせる)
		したがって模倣風では本質的に 紅魔郷 から 風神録0.02a までのゲームバランスは再現できない事を仕様とする。
		これは仮に弾幕が同じ場合でも、違う動き(違う避け方)が出来てしまう為。
	*/
	#else
	/* 風神録 の0.02a以降 */
	/*
		256固定小数点で自機の移動量
		1.0[pixel]	 == 256 == t256(1.0),			縦横の場合
		約0.7[pixel] == 181 == t256(1.0/√2.0)		斜めの場合
	 */
	static const s16 jiki_move_length[16][2] =
	{
	/* LDRU */ /* y x */
	// 斜め移動が速過ぎるのを修正。
	/* 0000 */ {	  0,	0},
	/* 0001 */ {	  0, -256},/* 0 U */
	/* 0010 */ {	256,	0},/* 2 R */
	/* 0011 */ {	181, -181},/* 1 UR */
	/* 0100 */ {	  0,  256},/* 4 D */
	/* 0101 */ {	  0,	0},
	/* 0110 */ {	181,  181},/* 3 DR */
	/* 0111 */ {	  0,	0},
	/* 1000 */ {   -256,	0},/* 6 L */
	/* 1001 */ {   -181, -181},/* 7 UL */
	/* 1010 */ {	  0,	0},
	/* 1011 */ {	  0,	0},
	/* 1100 */ {   -181,  181},/* 5 DL */
	/* 1101 */ {	  0,	0},
	/* 1110 */ {	  0,	0},
	/* 1111 */ {	  0,	0},
	};
	/*
		pspの画面は小さい為、斜め移動が速いのが目立つ。(おそらく画面が大きければ、余り気にならない)
		(紅魔郷 から 風神録0.02a までは、斜め移動が速い。が、余り気にならない)
		斜め移動が速いのが違和感があるので、斜め移動は補正する。
	*/
	#endif






/* 花映塚会話何たらサイト http://ambriel.hp.infoseek.co.jp/th9/  基本性能比較 移動速度(高速モード)
														[51200/xxxF]
200/50		50F 文										0x0400[1024.000000000000000000000000000000]3.63636363636363636363636363636364
200/55		55F [魔理沙] ミスティア (メディ,  四季) 	0x03a3[ 930.909090909090909090909090909091]3.63636363636363636363636363636364
200/58		58F [チルノ]								0x0373[ 882.758620689655172413793103448276]3.44827586206896551724137931034483
200/61		61F (鈴仙,	ルナサ) てゐ					0x0347[ 839.344262295081967213114754098361]3.27868852459016393442622950819672		[REMILIA]
200/65		65F リリカ									0x0314[ 787.692307692307692307692307692308]3.07692307692307692307692307692308
200/67		67F 小町									0x02fc[ 764.179104477611940298507462686567]2.98507462686567164179104477611940
200/68		68F [霊夢] 咲夜 							0x02f1[ 752.941176470588235294117647058824]2.94117647058823529411764705882353
200/72		72F メルラン								0x02c7[ 711.111111111111111111111111111111]2.77777777777777777777777777777778		[YUYUKO]
200/91		91F 幽香									0x0233[ 562.637362637362637362637362637363]2.19780219780219780219780219780220

吸霊移動速度(低速モード)
200/79		79F 	文									0x0288[ 648.101265822784810126582278481013]2.53164556962025316455696202531646
200/80		80F 	ミスティア							0x0280[ 640.000000000000000000000000000000]2.50000000000000000000000000000000
200/83		83F 	[チルノ]							0x0269[ 616.867469879518072289156626506024]2.40963855421686746987951807228916
200/85		85F 	咲夜								0x025a[ 602.352941176470588235294117647059]2.35294117647058823529411764705882
200/91		91F 	[魔理沙]							0x0233[ 562.637362637362637362637362637363]2.19780219780219780219780219780220
200/109 	109F	(鈴仙,	ルナサ) 					0x01d6[ 469.724770642201834862385321100917]1.83486238532110091743119266055046		[REMILIA]
200/114 	114F	(メディ,  四季) 					0x01c1[ 449.122807017543859649122807017544]1.75438596491228070175438596491228
200/124 	124F	リリカ 小町 						0x019d[ 412.903225806451612903225806451613]1.61290322580645161290322580645161
200/130 	130F	妖夢								0x018a[ 393.846153846153846153846153846154]1.53846153846153846153846153846154
200/136 	136F	メルラン [霊夢] 					0x0178[ 376.470588235294117647058823529412]1.47058823529411764705882352941176
200/145 	145F	てゐ								0x0161[ 353.103448275862068965517241379310]1.37931034482758620689655172413793		[YUYUKO]
200/148 	148F	幽香								0x015a[ 345.945945945945945945945945945946]1.35135135135135135135135135135135

 */
/*
http://wikiwiki.jp/let/?etc%2F%C3%CE%BC%B1%2F%BC%AB%B5%A1%A4%CE%B0%DC%C6%B0%C2%AE%C5%D9

速度の単位はドット毎フレーム。

(東方)
キャラ		高速 低速
(紅魔郷)
霊夢		4.0 2.0
魔理沙		5.0 2.5
-------------------
(妖々夢)
霊夢		4.0 1.6
魔理沙		5.0 2.0
咲夜		4.0 2.2
-------------------
(永夜抄)
結界組		4.0 2.0 (霊夢+紫)
詠唱組		5.0 2.2 (魔理沙+アリス)
紅魔組		4.0 2.3 (咲夜+レミリア)
冥界組		5.0 1.9 (幽々子+妖夢)
-------------------
霊夢		4.0 2.0 紫			4.0 2.0
魔理沙		5.0 2.2 アリス		4.0 2.2 (速い方へ合わせる)
咲夜		4.0 2.3 レミリア	5.0 2.3 (遅い方へ合わせる)
妖夢		5.0 1.9 幽々子		4.0 1.9 (速い方へ合わせる)
-------------------
(花映塚)
文			5.5 3.5

ミスティア	5.0 3.4
魔理沙		5.0 3.0
メディスン	5.0 2.4
四季映姫	5.0 2.4
妖夢		5.0 2.1

チルノ		4.7 3.3

鈴仙		4.5 2.5
ルナサ		4.5 2.5
てゐ		4.5 1.9

リリカ		4.2 2.2
小町		4.1 2.2

咲夜		4.0 3.2
霊夢		4.0 2.0

メルラン	3.8 2.0
幽香		3.0 1.8
-------------------
(文花帖)
文			5.0 2.3 0.5(超精密)[*1] [*1] 超精密は0.5
-------------------
(風神録0.02a)
霊夢		4.5 2.0
魔理沙AB	5.0 2.0
魔理沙C 	5.0 3.0
-------------------
(風神録)
霊夢		4.5 (斜3.18)[*2] 2.0 (斜1.41)[*3]
魔理沙		5.0 (斜3.53)[*4] 2.0 (斜1.41)[*5]

[*2] 斜め移動の場合、x軸方向とy軸方向に3.18ドット移動[*3] 斜め移動の場合、x軸方向とy軸方向に1.41ドット移動
[*4] 斜め移動の場合、x軸方向とy軸方向に3.53ドット移動[*5] 斜め移動の場合、x軸方向とy軸方向に1.41ドット移動
*/


//#define BASE_SPEED_MINIMUM		(PLAYERS8*4)
//#define BASE_SPEED_MAXIMUM		(PLAYERS8*5)
//	 2,  3,  4,  7,  3, 	/* 最低速度 player_speed_minimum */
//	 4,  5,  4,  7,  3, 	/* 最高速度 player_speed_maximum */

	/* 高速モード(通常時) */					/* 高速モード(ボム発動時) */
	#if (1)/*(模倣風)*/
		#define SPEED_HIGH_REIMU_A		(0x02f1)	/* t256(2.94) 2.94140625		  t256(3.0), */
		#define SPEED_HIGH_REIMU_B		(0x02f1)	/* t256(2.94) 2.94140625		  t256(3.0), */
		#define SPEED_HIGH_MARISA_A 	(0x03a3)	/* t256(3.64) 3.63671875		  t256(2.0), */
		#define SPEED_HIGH_MARISA_B 	(0x03a3)	/* t256(3.64) 3.63671875		  t256(2.0), */
		#define SPEED_HIGH_REMILIA		(0x0347)	/* t256(3.28) 3.27734375		  t256(5.0), */
		#define SPEED_HIGH_YUYUKO		(0x02c7)	/* t256(2.78) 2.77734375		  t256(5.0), */
		#define SPEED_HIGH_CIRNO_A		(0x0373)	/* t256(3.45) 3.44921875		  t256(4.5), */ 	/* ⑨だから低速の方が速い */
		#define SPEED_HIGH_CIRNO_Q		(0x0373)	/* t256(3.45) 3.44921875		  t256(4.5), */ 	/* ⑨だから低速の方が速い */
												/* 低速モード(通常時) */							/* 低速モード(ボム発動時) */
		#define SPEED_LOW_REIMU_A		(0x0178)	/* t256(1.47) 1.46875000 t256(2.0) t256(2.0), */
		#define SPEED_LOW_REIMU_B		(0x0178)	/* t256(1.47) 1.46875000 t256(2.0) t256(2.0), */
		#define SPEED_LOW_MARISA_A		(0x0233)	/* t256(2.20) 2.19921875 t256(2.5) t256(2.0), */
		#define SPEED_LOW_MARISA_B		(0x0233)	/* t256(2.20) 2.19921875 t256(2.5) t256(2.0), */
		#define SPEED_LOW_REMILIA		(0x01d6)	/* t256(1.84) 1.83593750 t256(2.5) t256(4.0), */
		#define SPEED_LOW_YUYUKO		(0x0161)	/* t256(1.38) 1.37890625 t256(2.0) t256(4.5), */
		#define SPEED_LOW_CIRNO_A		(0x0269)	/* t256(2.41) 2.41015625 t256(7.0) t256(5.0), */ /* 0x0700 ⑨だから低速の方が速い 0x0400==文高速時==幻想郷最速？ */
		#define SPEED_LOW_CIRNO_Q		(0x0700)	/* t256(2.41) 2.41015625 t256(7.0) t256(5.0), */ /* 0x0700 ⑨だから低速の方が速い 0x0400==文高速時==幻想郷最速？ */
	#else/*(こちらのタイプの方が作者本来のイメージに近いのかも知れないが、pspでは面白くない。)*/
		#define SPEED_HIGH_REIMU_A		(0x0300)	/* t256(3.000) 3.000 == 4.0x0.75 (紅魔郷, 妖々夢, 永夜抄, 花映塚) */
		#define SPEED_HIGH_REIMU_B		(0x0300)	/* t256(3.000) 3.000 == 4.0x0.75 (紅魔郷, 妖々夢, 永夜抄, 花映塚) */
		#define SPEED_HIGH_MARISA_A 	(0x03c0)	/* t256(3.750) 3.750 == 5.0x0.75 (紅魔郷, 妖々夢, 永夜抄, 花映塚, 風神録) */
		#define SPEED_HIGH_MARISA_B 	(0x03c0)	/* t256(3.750) 3.750 == 5.0x0.75 (紅魔郷, 妖々夢, 永夜抄, 花映塚, 風神録) */
		#define SPEED_HIGH_REMILIA		(0x03c0)	/* t256(3.750) 3.750 == 5.0x0.75 ( 永夜抄[単] ) (4.0==永夜抄[組],  咲夜 < レミリア) */
		#define SPEED_HIGH_YUYUKO		(0x0300)	/* t256(3.000) 3.000 == 4.0x0.75 ( 永夜抄[単] ) (5.0==永夜抄[組],  幽々子 < 妖夢) */
		#define SPEED_HIGH_CIRNO_A		(0x0386)	/* t256(3.525) 3.525 == 4.7x0.75 (花映塚)  (但し花映塚は番外編なので、本編で出たとすると違う調整になる可能性の方が高い)  */
		#define SPEED_HIGH_CIRNO_Q		(0x0386)	/* t256(3.525) */	/* ⑨だから低速の方が速い */
												/* 低速モード(通常時) */							/* 低速モード(ボム発動時) */
		#define SPEED_LOW_REIMU_A		(0x0180)	/* t256(1.500) 1.500 == 2.0x0.75 (紅魔郷, 永夜抄, 花映塚, 風神録) (1.60妖々夢) */
		#define SPEED_LOW_REIMU_B		(0x0180)	/* t256(1.500) 1.500 == 2.0x0.75 (紅魔郷, 永夜抄, 花映塚, 風神録) (1.60妖々夢) */
		#define SPEED_LOW_MARISA_A		(0x01e0)	/* t256(1.875) 1.875 == 2.5x0.75 (2.50紅魔郷) (2.00妖々夢) (2.20永夜抄) (3.00花映塚) (2.00風神録) (3.00風神録C) */
		#define SPEED_LOW_MARISA_B		(0x0240)	/* t256(2.250) 2.250 == 3.0x0.75 (2.50紅魔郷) (2.00妖々夢) (2.20永夜抄) (3.00花映塚) (2.00風神録) (3.00風神録C) */
		#define SPEED_LOW_REMILIA		(0x01b9)	/* t256(1.725) 1.725 == 2.3x0.75 ( 永夜抄[単] ) (2.3==永夜抄[組],  咲夜 < レミリア) */
		#define SPEED_LOW_YUYUKO		(0x016c)	/* t256(1.425) 1.425 == 1.9x0.75 ( 永夜抄[単] ) (1.9==永夜抄[組],  幽々子 < 妖夢) */
		#define SPEED_LOW_CIRNO_A		(0x0279)	/* t256(2.475) 2.475 == 3.3x0.75 (花映塚)  (但し花映塚は番外編なので、本編で出たとすると違う調整になる可能性の方が高い)  */
		#define SPEED_LOW_CIRNO_Q		(0x0700)	/* t256(7.000) ⑨だから低速の方が速い 0x0580==文高速時==幻想郷最速？ */
	#endif

	#define PLAYER_WIDTH			(50)	/*	固定サイズ */
	#define PLAYER_HEIGHT			(50)	/*	固定サイズ */

	static const signed /* int */short player_speed256[(PLAYERS8*4)] =
	{	/* 高速モード(通常時) */	/* 高速モード(ボム発動時) */
		SPEED_HIGH_REIMU_A, 		/* REIMU_A */
		SPEED_HIGH_REIMU_B, 		/* REIMU_B */
		SPEED_HIGH_MARISA_A,		/* MARISA_A */
		SPEED_HIGH_MARISA_B,		/* MARISA_B */
		SPEED_HIGH_REMILIA, 		/* REMILIA */
		SPEED_HIGH_YUYUKO,			/* YUYUKO */
		SPEED_HIGH_CIRNO_A, 		/* CIRNO_A */
		SPEED_HIGH_CIRNO_Q, 		/* CIRNO_Q */
		/* 低速モード(通常時) */	/* 低速モード(ボム発動時) */
		SPEED_LOW_REIMU_A,			/* REIMU_A */
		SPEED_LOW_REIMU_B,			/* REIMU_B */
		SPEED_LOW_MARISA_A, 		/* MARISA_A */
		SPEED_LOW_MARISA_B, 		/* MARISA_B */
		SPEED_LOW_REMILIA,			/* REMILIA */
		SPEED_LOW_YUYUKO,			/* YUYUKO */
		SPEED_LOW_CIRNO_A,			/* CIRNO_A */
		SPEED_LOW_CIRNO_Q,			/* CIRNO_Q */
	#if 0/* [マスタースパーク中は、速度半分。] */
		/* 高速モード(通常時) */	/* 高速モード(ボム発動時) */
		SPEED_HIGH_REIMU_A, 		/* REIMU_A */
		SPEED_HIGH_REIMU_B, 		/* REIMU_B */
		SPEED_HIGH_MARISA_A,		/* MARISA_A */
		(SPEED_HIGH_MARISA_B>>1),	/* MARISA_B */
		SPEED_HIGH_REMILIA, 		/* REMILIA */
		SPEED_HIGH_YUYUKO,			/* YUYUKO */
		SPEED_HIGH_CIRNO_A, 		/* CIRNO_A */
		SPEED_HIGH_CIRNO_Q, 		/* CIRNO_Q */
		/* 低速モード(通常時) */	/* 低速モード(ボム発動時) */
		SPEED_LOW_REIMU_A,			/* REIMU_A */
		SPEED_LOW_REIMU_B,			/* REIMU_B */
		SPEED_LOW_MARISA_A, 		/* MARISA_A */
		(SPEED_LOW_MARISA_B>>1),	/* MARISA_B */
		SPEED_LOW_REMILIA,			/* REMILIA */
		SPEED_LOW_YUYUKO,			/* YUYUKO */
		SPEED_LOW_CIRNO_A,			/* CIRNO_A */
		SPEED_LOW_CIRNO_Q,			/* CIRNO_Q */
	#endif
	};
	/* 自機速度を決める。 */
	unsigned int is_slow;
	is_slow = (psp_pad.pad_data & PSP_KEY_SLOW);
	/* const */ signed int my_speed = player_speed256[(cg_game_select_player) + ((is_slow)?(PLAYERS8):(0))];
	/* 移動量を決める。(移動量 = 自機速度 x アナログキー、デジタルの場合は予めアナログキー移動量に変換してある) */
	#if 1/* [マスタースパーク中は、速度半分。] */
	if (
		(MARISA_B==(cg_game_select_player)) &&	/* 魔理沙B(恋符) */
		(0<cg.bomber_time)				/* マスタースパーク中 */
	)
		#if 0
	{
		;/* マスタースパーク中はショットが撃てないらしい */
	}
	if (is_master_spark)
		#endif
	{	(my_speed >>= 1);	}
	#endif
	/* 斜めを考慮して移動する。 */
	s1->center.x256 += ((((signed int)(jiki_move_length[((psp_pad.pad_data&0xf0)>>4)][0]))*(my_speed))>>8); 	/* fps_factor */
	s1->center.y256 += ((((signed int)(jiki_move_length[((psp_pad.pad_data&0xf0)>>4)][1]))*(my_speed))>>8); 	/* fps_factor */
	/* 画面外に、はみだしたら修正。(中心座標で判定) */
/*(r35-)*/
//		 if (s1->center.x256 < t256(GAME_X_OFFSET)) {s1->center.x256 = t256(GAME_X_OFFSET); }/* 左チェック(喰み出さない) */
//	else if (s1->center.x256 > t256(GAME_WIDTH) )	{s1->center.x256 = t256(GAME_WIDTH);	}/* 右チェック(喰み出さない) */
//		 if (s1->center.y256 < t256(0)) 			{s1->center.y256 = t256(0); 			}/* 上チェック(上が喰み出すか、喰み出さないかまだ仕様が決まってない) */
//	else if (s1->center.y256 > t256(GAME_HEIGHT))	{s1->center.y256 = t256(GAME_HEIGHT);	}/* 下チェック(下が喰み出すのは意図的) */
	/* 喰み出さない分[pixel] */
	#define ADJUST_JIKI_WIDTH	(8)
	s1->center.x256 = psp_min(s1->center.x256, t256(GAME_WIDTH-ADJUST_JIKI_WIDTH)); 		/* 右チェック(喰み出す) */
	s1->center.x256 = psp_max(s1->center.x256, t256(GAME_X_OFFSET+ADJUST_JIKI_WIDTH));		/* 左チェック(喰み出す) */
	s1->center.y256 = psp_min(s1->center.y256, t256(GAME_HEIGHT));							/* 下チェック(下が喰み出すのは意図的) */
	s1->center.y256 = psp_max(s1->center.y256, t256(0));									/* 上チェック(上が喰み出すか、喰み出さないかまだ仕様が決まってない) */
	/*	psp は、弾でゲーム性を再現するには、いくらなんでも上下が狭すぎる。
		上下が喰み出すのはゲーム性と、ゲーム画面設計の両方の問題で意図的である。
		ゲーム画面設計上は左右は喰み出しても良いのだが、模倣風では喰み出さない事にする。
		これは左右の壁で反射する弾処理が、喰み出し可だと遅くなりそうなので都合上の問題。
		咲夜さんの上避けは何時になったら出来るのやら。 */
	/* コア移動 */
	{
		OBJ *s2;
	//	s2 = obj_maru;
		s2 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
		/* Gu(中心座標) */
		s2->center.x256 = s1->center.x256;
		s2->center.y256 = s1->center.y256;
		/* 低速モード用エフェクトの表示 */
		{
			OBJ *obj_tei_soku;
//			obj_tei_soku					= obj_effect[TEISOKU_EFFECT_00_OBJ];
			obj_tei_soku					= &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_15_JIKI_TEISOKU_EFFECT];
			if (is_slow)	/* 低速モード用エフェクト、○、表示 */
			{
//				OBJ *zzz_obj_maru;
//				zzz_obj_maru					= &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
				obj_tei_soku->obj_type_set		= (SPELL_SQUERE_);
				obj_tei_soku->center.x256		= (s1->center.x256);	/* 中心座標 */
				obj_tei_soku->center.y256		= (s1->center.y256);	/* 中心座標 */
				#if 1
				/* 描画用角度(下が0度で左回り(反時計回り)) */
				obj_tei_soku->rotationCCW1024 += (10);
				#endif
			}
			else	/* 低速モード用エフェクト、○、非表示 */
			{
				obj_tei_soku->obj_type_set		= (SP_DUMMY_MUTEKI);
			//	obj_tei_soku->center.y256			= (t256(300));	/* 中心座標 */
			}
		}
	}
	/* MAX時のアイテム自動収集 */
	if (psp_pad.pad_data & PSP_KEY_UP/* PSP_CTRL_UP */) /* 註：斜め上でも回収可能 */ /* && (s1->y>0) */
	{
		#if 1
			/* 全キャラ: アイテム上部収集がいつでも可能 */
		#else
		if ((cg.weapon_power==MAX_POWER_IS_128) 	// 128 変更 /* max==MAX_POWER_IS_128==「129段階」 */
			/* 魔理沙 特殊能力：アイテム上部収集がいつでも可能 */
			|| (MARISA_A==(cg_game_select_player))
			|| (MARISA_B==(cg_game_select_player))
		//	|| (MARISA_C==(cg_game_select_player))
		)	/* 魔理沙は常に上部自動収集が可能 */
		#endif
		{
			if (s1->center.y256 < ITEM_GET_BORDER_LINE256)/* [アイテム引き寄せライン] */
			{
				cg.state_flag |= JIKI_FLAG_0x0010_JYOU_BU_SYUU_SYUU;	/* 上部自動収集可能 */
			}
		}
	}
	else
	if (psp_pad.pad_data & PSP_KEY_DOWN)	/* 註：斜め下でもやめる */ /* PSP_CTRL_DOWN */
	{
		//if (cg.state_flag & (JIKI_FLAG_0x0010_JYOU_BU_SYUU_SYUU /* | JIKI_FLAG_0x0020_BOMBER_SYUU_SYUU */) )/* ???たぶん */
		{
			cg.state_flag &= (~JIKI_FLAG_0x0010_JYOU_BU_SYUU_SYUU); 	/* 上部自動収集不可 */
		}
	}
//
		/*---------------------------------------------------------
			プレイヤーショット関連処理
		---------------------------------------------------------*/
	/* シナリオ会話モードではショットボタン入力無効 */
	if (IS_SCENE_KAIWA_TATAKAU)
	{
		if (psp_pad.pad_data & PSP_KEY_SHOT_OK)
		{
			cg.state_flag |= JIKI_FLAG_0x0080_SHOT_KEY_SEND_FOR_OPTION; 	/* on(オプションがショットを撃つ) */
			register_main_shot(s1);
		}
	}
	#if 0/* デバッグ用 */
	p d_my_score	= (cg.jiki_weapon_level_offset);/* デバッグ */
	p d_graze_point = (cg.jiki_weapon_level_offset);/* デバッグ */
	#endif

	/*---------------------------------------------------------
		プレイヤーアニメーション関連処理
	---------------------------------------------------------*/
	{static int anime_delay;
		anime_delay -= 1;	/* fps_fa_ctor */
		if (0 > anime_delay)
		{
			anime_delay = jiki_shot_get_player_animation_speed();
			//
			static int auto_anime_frame = (4);/* 5 */
				 if (psp_pad.pad_data & PSP_KEY_LEFT/* PSP_CTRL_LEFT */)	{	if ((0) < auto_anime_frame) 	{auto_anime_frame--;} }
			else if (psp_pad.pad_data & PSP_KEY_RIGHT/* PSP_CTRL_RIGHT */)	{	if ((8) > auto_anime_frame) 	{auto_anime_frame++;} }
			else
			{
				if (auto_anime_frame>4/* 5 */) auto_anime_frame--;
				if (auto_anime_frame<4/* 5 */) auto_anime_frame++;
			}
			#if 1
			{
				int now_anime_frame;
				static int auto_aniime;
				auto_aniime++;
				auto_aniime &= 3;
					 if (4==auto_anime_frame)	{	now_anime_frame = (auto_anime_frame + auto_aniime); }	/* 中心1-4 */
				else if (4<auto_anime_frame)	{	now_anime_frame = (auto_anime_frame + (3) + (8) );	}	/* 右側1-4 */	/* +(8) == オプションインターリーブ */
				else							{	now_anime_frame = (auto_anime_frame );				}	/* 左側1-4 */
				s1->obj_type_set = (JIKI_PLAYER_00_LEFT)+(now_anime_frame);
			}
			#else
			{
				static int auto_aniime;
				auto_aniime++;
				auto_aniime &= 3;
				s1->obj_type_set = (JIKI_PLAYER_00_LEFT)+(auto_anime_frame );
					 if (4==auto_anime_frame)	{	s1->obj_type_set += ( auto_aniime); }	/* 中心1-4 */
				else if (4<auto_anime_frame)	{	s1->obj_type_set += ( 3+8); 		}	/* 右側1-4 */
			//	else							{										}	/* 左側1-4 */
			}
			#endif
		}
	}
/*
0 1 2 3 4 5 6  7  8  :: auto_anime_frame[0 to 8]
0 1 2 3 4 8 9 10 11  :: now_anime_frame [0 to 11]
		5
		6
		7
 */
}

/*---------------------------------------------------------
	武器レベルが変更された場合に、武器やオプションの状態をチェックして変更
---------------------------------------------------------*/
/* [cg.weapon_powerが変更された場合に必ず行う後チェック] */
static void check_weapon_level(void)
{
	/*---------------------------------------------------------
		武器の段階を決める
	---------------------------------------------------------*/
	// weaponの段階から今の装備を決める 	// リストを見て装備の変更
	// 最大129へ。
	// (0-128の129段階に修正)
	#if 0//
	/* いろいろ頑張ってみたが、元の調整(6,11,61,86)は誰得(?)なので変える(2倍を超える値の調整は意味無い気ががする) */
	u8 pds_weapon;	pds_weapon = cg.weapon_power;
		 if (pds_weapon < ( 8)) 	{	cg.jiki_weapon_level_offset = (WEAPON_L0<<3);	}	/* WEAPON_L0(P000-P008) */	/* 6 */
	else if (pds_weapon < ( 16))	{	cg.jiki_weapon_level_offset = (WEAPON_L1<<3);	}	/* WEAPON_L1(P008-P015) */	/* 11 */
	else if (pds_weapon < ( 32))	{	cg.jiki_weapon_level_offset = (WEAPON_L2<<3);	}	/* WEAPON_L2(P016-P031) */	/* 61 */
	else if (pds_weapon < ( 64))	{	cg.jiki_weapon_level_offset = (WEAPON_L3<<3);	}	/* WEAPON_L3(P032-P063) */	/* 86 */
	else if (pds_weapon < (128))	{	cg.jiki_weapon_level_offset = (WEAPON_L4<<3);	}	/* WEAPON_L4(P064-P127) */
	else							{	cg.jiki_weapon_level_offset = (WEAPON_L5<<3);	}	/* WEAPON_L5(P128)		 */ /* max==P128==「129段階」 */
	cg.jiki_weapon_level_offset += (cg_game_select_player);
	#endif
	#if 1//
	u8 pds_weapon;	pds_weapon = cg.weapon_power;
	/* 0000 0001 1111 1---*/
	/* 紅、調べたら丁度2倍っぽい。 */
	{	/* 丁度2倍だとこんな感じで簡略化できる。 */
	//	cg.jiki_weapon_level_offset = ((cg_game_select_player)/* 0 */);
	//	cg.jiki_weapon_level_offset += (WEAPON_L5<<3);
	//	cg.jiki_weapon_level = ((0)/* 0 */);
		cg.jiki_weapon_level = (WEAPON_L5);
		unsigned int jj;
		for (jj=(0); jj<(5); jj++)
		{
			if (pds_weapon & ((0x80)>>jj))
			{
				goto loop_end;//break;
			}
		//	cg.jiki_weapon_level_offset -= (0x08);
			cg.jiki_weapon_level -= (0x01);
		}
		loop_end:;
	}/*
0000 0000 0000 0000
		  5432 1 0
		  0123 4
 */
	#endif
//
	/*---------------------------------------------------------
		プレイヤーオプションチェック(必要であればオプションをセット)
	---------------------------------------------------------*/
	#if 0/* (r32) */
	{
		/* いろいろ頑張ってみたが、元の調整(35,55,80,108)は誰得(?)なので変える(2倍を超える値の調整は意味無い気ががする) */
	//	static const u8 jjj_tbl[4] =
	//	{
	//		( 8),		// (35-1),
	//		(16),		// (55-1),
	//		(32),		// (80-1),
	//		(64)		// (108-1),
	//	};
		unsigned int jj;
		for (jj=(0); jj<(4); jj++)/* オプションは4つ */
		{
			OBJ *zzz_obj_option;
			zzz_obj_option = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_04_JIKI_OPTION0+jj];
			if ((pds_weapon > ((0x08)<<jj)/* jjj_tbl[jj] */))	/* 丁度2倍だとこんな感じで簡略化できる。 */
			{
				/* オプション登場 */
				/* もし新規登場なら */
				if (PL_OPTION_FLAG_00_OPTION_OFF==(zzz_obj_option->PL_OPTION_DATA_yuukou_flag) )
				{
					zzz_obj_option->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_01_OPTION_ON);	// 可視フラグのOn(可視)
					const OBJ *s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
					zzz_obj_option->center.x256 = s1->center.x256;
					zzz_obj_option->center.y256 = s1->center.y256;
				}
			}
			else
			{
				/* オプション隠す */
				zzz_obj_option->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_00_OPTION_OFF);	// 可視フラグのOFF(不可視)
				zzz_obj_option->center.y256=t256(GAME_HEIGHT+1+16);
			}
		}
	}
	#endif
	#if 1/* (r33)チルノはともかく左右対称じゃないとかっこ悪い気がしてきた。 */
	{
		/* いろいろ頑張ってみたが、元の調整(35,55,80,108)は誰得(?)なので変える(2倍を超える値の調整は意味無い気ががする) */
	//	static const u8 jjj_tbl[4] =
	//	{
	//		( 8),		// (35-1),
	//		(16),		// (55-1),
	//		(32),		// (80-1),
	//		(64)		// (108-1),
	//	};
	// jj0 00
	// jj1 01
	// jj2 10
	// jj3 11
		unsigned int jj;
		for (jj=(0); jj<(4); jj++)/* オプションは4つ */
		{
			OBJ *option_s1;
			option_s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_04_JIKI_OPTION0+jj];
			const u8 jjj_tbl[4] = /* オプションの出現条件 */
			{
				( 8-1), 	// オプション#0はpower 8以上で付く。
				( 8-1), 	// オプション#1はpower 8以上で付く。
				(96-1), 	// オプション#2はpower96以上で付く。
				(96-1), 	// オプション#3はpower96以上で付く。
			};
			if ((pds_weapon > jjj_tbl[jj]) )/* オプションの出現条件 */
			{
				/* オプション登場 */
				/* もし新規登場なら */
				if (PL_OPTION_FLAG_00_OPTION_OFF==(option_s1->PL_OPTION_DATA_yuukou_flag) )
				{
					option_s1->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_01_OPTION_ON);	// 可視フラグのOn(可視)
					const OBJ *s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
					option_s1->center.x256 = s1->center.x256;
					option_s1->center.y256 = s1->center.y256;
				}
			}
			else
			{
				/* オプション隠す */
				option_s1->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_00_OPTION_OFF); 	// 可視フラグのOFF(不可視)
				option_s1->center.y256 = t256(GAME_HEIGHT+1+16);
			}
		}
	}
	#endif
}

/*---------------------------------------------------------
	プレイヤーとアイテムのあたり判定1(アイテム専用)
	-------------------------------------------------------
		src 	プレイヤー
		ttt 	アイテム
---------------------------------------------------------*/
static int player_add_power_ttt_type(OBJ/**/ *src, u8 ttt_type)
{
		int add_score_point;
	{	const u8 aaa[4] = { 1, 8, 127, 1/* チルノA用 */};
	//	const int add_power = aaa[/* ((ttt_type)) */((NULL==ttt)?(0/* 3 チルノ用 */):((ttt->type)&0x03))];
		const int add_power = aaa[( ((ttt_type)&0x03))];
		int previous_power; previous_power = cg.weapon_power;		/* アイテム取得する直前のパワー値 */
		cg.weapon_power += add_power;	/* パワー値、加算 */
		/* パワー値、超えてたら修正 */
		#if (0)
		if ((MAX_POWER_IS_128-1) < cg.weapon_power )/* 127==128段階目 */	{	cg.weapon_power = MAX_POWER_IS_128;/* 最大値 */ 	}
		#else/*(ok?)*/
		cg.weapon_power = psp_min(cg.weapon_power, (MAX_POWER_IS_128));
		#endif
		if (MAX_POWER_IS_128 == cg.weapon_power/* previous_power */) /* maxの場合 */
		{
			if (previous_power != cg.weapon_power)/* 直前がMAXじゃなかったのに、今回MAXになった場合 */
			{
				#if 1
				/* 特殊機能 */
				bullets_to_hosi();/* 弾全部、星アイテムにする */
				#endif
			}
			cg.chain_point += add_power;	/* チェイン、加算 */
			/* チェイン、超えてたら修正 */
			#if (0)
			if (31 < cg.chain_point)	{	cg.chain_point = 31;/* 最大値 */	}
			#else/*(ok?)*/
			cg.chain_point = psp_min(cg.chain_point, (31));
			#endif
			/* (ノーミスボーナス)ウェポンボーナス得点計算 */
			add_score_point = (/* score_type */(cg.chain_point));
			#if 1
			/* チェインはボムMAXでないと実質、貯まらない */
				#if 0
		//	if (NULL==ttt)/* チルノなら */
				#else
			/* レミリア & 幽々子 & チルノは、ボム消費型(基本的にあまり貯めないでどんどん使う==割と直ぐ貯まる)にしようかと。 */
			if ((REMILIA-1) < (cg_game_select_player))/* レミリア & 幽々子 & チルノなら */
				#endif
			{
				if ((8-1) < cg.bombs)	{	;	}/* 既に最大値(8)ならば、なにもせず。 */
				else
				{
					cg.bombs++; 	/* ボム追加 */
					cg.weapon_power = (MAX_POWER_IS_128>>1);/* 最大値の半分 */
				}
			}
			#endif
		}
		else	/* maxでない場合、得点計算 */
		{
			/* (MAX時以外の) [P]は10点 */
			/* (MAX時以外の) [P中]は80点 */
			add_score_point = ((add_power/*-1 */)/* SCORE_10 */);
		}
	}
	check_weapon_level();/* [cg.weapon_powerが変更された場合に必ず行う後チェック] */
//
	voice_play_menu(VOICE05_BONUS, TRACK06_ITEM);/* テキトー */
	return (add_score_point);
}
/* http://hossy.info/game/toho/k_score.php
B アイテムの点数
難易度	通常：下   通常：上 1px毎 引き寄せ
easy	27800	   60000	 100 100000
normal	27800	   60000	 100 100000
hard	42040	  100000	 180 150000
lunatic 63330	  150000	 270 200000
extra	71200	  200000	 400 300000

---------------
「アイテム引き寄せライン」以下で取ると「アイテム引き寄せライン」から322ラインまで距離で減点。

プレイフィールドは 384x448 なので、448-322 == 126
「アイテム引き寄せライン」は多分上から128ドットかな？

(Bアイテムの大きさが16x16[pixel]なので、Bアイテムの消失判定は 448+(16/2)ラインで行うから、
最後にBアイテムの判定があるのが、BアイテムのＹ軸中心が456[ライン]にきた場合。
456-322 == 134, 134-128 == 6. この6[ライン]はそもそも自機中心が画面下部に行けない分が数ドット(5[pixel]?)ある。
残り1[pixel]は不等号で判定したから? )
---------------
模倣風ではＢ取って加点は無い(r33現在)。
 */
static OBJ_CALL_FUNC(player_collision_check_item)/* , int mask */ /* ,OBJ_Z03_ITEM */
{
	/* 自機がアイテムにあたった場合 */
	OBJ *ttt;	//対象
	ttt = obj_collision_check_00_tama(src, OBJ_Z03_ITEM); /* 弾専用(アイテム) */	/* mask */
	if (NULL != ttt)
	{
		const void *aaa_aaa[(8)] =
		{
			&&case_POWER_UP,				// case_SP_ITEM_00_P001
			&&case_POWER_UP,				// case_SP_ITEM_01_P008
			&&case_POWER_UP,				// case_SP_ITEM_02_P128
			&&case_SP_ITEM_03_1UP,			// case_SP_ITEM_03_1UP
			//
			&&case_SP_ITEM_04_BOMB, 		// case_SP_ITEM_04_BOMB
			&&case_SP_ITEM_05_TENSU,		// case_SP_ITEM_05_TENSU
			&&case_break,					// case_SP_ITEM_06_HOSI 	星点は、ここで処理しない。及び星点は、あたり判定なし。
			&&case_break,					// case_SP_ITEM_07_SPECIAL
		};
		goto *aaa_aaa[((ttt->obj_type_set)&0x07)];
	//	case_SP_ITEM_00_P001:	//	player_add_power(src, ttt, 1);		break;	// ウェポンアイテム[小p]
	//	case_SP_ITEM_01_P008:	//	player_add_power(src, ttt, 8);		break;	// ウェポンアイテム[大P]
	//	case_SP_ITEM_02_P128:	//	player_add_power(src, ttt, 127);	break;	// ウェポンアイテム[F]
		case_POWER_UP:	// ウェポンアイテム[小p][大P][F]
			;
	//	if (NULL!=ttt)/* チルノ以外なら */
		{	const int add_score_point = player_add_power_ttt_type(src, ttt->obj_type_set);
			bonus_info_score_nodel(ttt, (add_score_point)/*add_score_point*/);
			/* */ttt->jyumyou = JYUMYOU_NASI;/* おしまい */
		}
			goto case_break;
		//
		case_SP_ITEM_04_BOMB:
			if ((8-1) < cg.bombs)	{	goto add_10000pts;	}/* 既に最大値(8)ならば、10000+ [pts] */
			cg.bombs++;
			#if 1/* バグfix? */
			ttt->jyumyou = JYUMYOU_NASI;/* おしまい */
			#endif
			voice_play_menu(VOICE05_BONUS, TRACK06_ITEM);/* テキトー */
			goto case_break;
		case_SP_ITEM_03_1UP:
			if ((8-1) < cg.zanki)	{	goto add_10000pts;	}/* 既に最大値(8)ならば、10000+ [pts] */
			cg.zanki++;
			#if 1/* バグfix? */
			ttt->jyumyou = JYUMYOU_NASI;/* おしまい */
			#endif
			voice_play_menu(VOICE06_EXTEND, TRACK01_PICHUN/*TRACK03_IVENT_DAN*/);/* テキトー */ /* effect_sound_number */
			goto case_break;
		case_SP_ITEM_05_TENSU:
			// チルノQの場合、点数アイテムでパワーアップ[p]power+1。
			if (CIRNO_Q == cg_game_select_player)/* 7:CIRNO_Q only. (r35-) */
			{	/*(チルノQの場合特別)*/
				ttt->obj_type_set = SP_ITEM_00_P001;	/* パワーアップ は[p]小 と同じ。 */
				goto case_POWER_UP;
			}
			else/*(通常)*/
			{
				/* ITEM_GET_BORDER_LINE256 より上で取ると 10000pts. ... 下で取ると(?)約100pts. */
				/* (大体90pts、非常に難しいが、がんばれば(消える直前の3ライン)70ptsまで可能らしい) */
				int add_score_point;
				if (ITEM_GET_BORDER_LINE256 < src->center.y256) /* ITEM_GET_BORDER_LINE256 未満の場合は、ITEM_GET_BORDER_LINE256までの距離に応じて減点 */
				{
				//	add_score_point -= ((ttt->center.y256-ITEM_GET_BORDER_LINE256)>>(4+8));
				//	add_score_point = ((/* 0x1f-(3) */(SCORE_9000)-((ttt->center.y256-ITEM_GET_BORDER_LINE256)>>(3+8)))/* &0x1f */);
					add_score_point = (SCORE_9000) - ((ttt->center.y256-ITEM_GET_BORDER_LINE256)>>(3+8));
				}
				else
				{
					add_10000pts:/* 強引に得点10000+ [pts] */
				//	add_score_point = (SCORE_10000);	/* 基本点 10000[pts] */
					add_score_point = (SCORE_10000+(cg.game_difficulty));	/* 基本点 10000[pts](easy), 11000(normal), 12000(hard), 512000(lunatic). */
				}
				bonus_info_score_nodel(ttt, add_score_point);
				/* */ttt->jyumyou = JYUMYOU_NASI;/* おしまい */
			}
			voice_play_menu(VOICE05_BONUS, TRACK06_ITEM);/* テキトー */
		case_break:
			;
	}
}
	//	case_SP_ITEM_06_HOSI:
	//	case_SP_ITEM_07_SPECIAL:
	//		goto case_break;
		#if 0
		/* 星点は、あたり判定なし */
		case_SP_ITEM_05_HOSI:		/* not_break; */
			ttt->jyumyou = JYUMYOU_NASI;/* 星点のみ特別処理 */
			voice_play(VOICE05_BONUS, TRACK06_ITEM);/* テキトー */
			goto case_break;
		#endif


/*---------------------------------------------------------
	ぴちゅーん処理(サブ)
	-------------------------------------------------------
	プレイヤーが 敵グループ または 敵弾 に当たった場合、
	喰らいボム開始の為の、ぴちゅーん処理を行う。
---------------------------------------------------------*/
static void player_explode(OBJ *s1);
extern int jiki_shot_get_kurai_bombtimer(void);/* 喰らいボムの入力受け付け時間を設定 */
static void player_set_pichuun(void)
{
	pds_status_timer	= jiki_shot_get_kurai_bombtimer();
	voice_play_menu(VOICE04_SHIP_HAKAI, /*TRACK03_IVENT_DAN*/TRACK01_PICHUN/* TRACK01_PICHUN */);/* 自機死に音は、なるべく重ねない */
	{
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
		player_explode(zzz_player);/* プレイヤー爆発 */
	}
}


/*---------------------------------------------------------
	アイテム以外のプレイヤーのあたり判定。
	-------------------------------------------------------
	「敵弾によるグレイズ」
	「敵弾による死亡」
	「敵(雑魚＆ボス)による死亡」
---------------------------------------------------------*/
	//	player_collision_check_graze(s1);	/* グレイズの当たり判定 */
	//	player_collision_check_teki(s1);	/* 雑魚＆ボスの当たり判定 */

#define TEST_FIX_GRAZE048	(t256(128.0))
#define TEST_FIX_DEATH001	(t256(1.0))
#define TEST_FIX_TEKI001	(t256(1.0))

static OBJ_CALL_FUNC(player_collision_check_tama)
{
	//static OBJ_CALL_FUNC(player_collision_check_graze)
	/*---------------------------------------------------------
		プレイヤーと敵弾のあたり判定2(グレイズ専用)
		-------------------------------------------------------
			src 	プレイヤー
			ttt 	敵弾
	---------------------------------------------------------*/
	#if (1)
	src->m_Hit256R		= TEST_FIX_GRAZE048;/* てすと、グレイズ判定。 */
	#endif
	OBJ *ttt;	/* 敵弾 */
	ttt = NULL;
	ttt = obj_collision_check_00_tama(src, OBJ_Z04_TAMA);/* 弾専用 */
	if (NULL != ttt)
	{
		/* プレイヤーに敵弾があたった場合はグレイズする */
		if (0==(ttt->hatudan_register_spec_data & TAMA_SPEC_4000_GRAZE))/* グレイズ済? */
		{
			ttt->hatudan_register_spec_data |= TAMA_SPEC_4000_GRAZE;/* グレイズ済 */
			cg.graze_point++;/* グレイズ数 */
			// チルノAとQの場合、グレイズでパワーアップ。
		//	if ((CIRNO_A-1) < cg_game_select_player)/* 6:CIRNO_A or 7:CIRNO_Q (-r34) */
			// チルノAの場合のみ、グレイズでパワーアップ。
			if (CIRNO_A == cg_game_select_player)/* 6:CIRNO_A only. (r35-) */
			{
				player_add_power_ttt_type(src, /* ttt->type */(3)/*(3==チルノA専用)*/);
			}
			else
			{
				player_dummy_add_score((score(100)+score(200)*(cg.game_difficulty)));/* score(500) */
			}
			/* グレイズ音 */
			voice_play_graze(); 	/* グレイズ音に関しては、専用の発音処理が必要。 */
		}
		#if 1
		/* プレイヤースプライトが弾に触れているか */
		{
			OBJ *uuu;	/* uuu */
			uuu = NULL;
		#if (0)
			OBJ *zzz_obj_maru;
			zzz_obj_maru = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
			/* (グレイズ中ならコアと敵弾のあたり判定をする) */
//			#if (0)
//			/* コアで判定(廃止) */
//			uuu = obj_collision_check_00_tama(zzz_obj_maru, OBJ_Z04_TAMA);/* 弾専用 */
//			#else
			/* 自機で判定 */
			int chache_m_Hit256R;
			chache_m_Hit256R	= src->m_Hit256R;/* 自機のあたり判定サイズ */
			src->m_Hit256R		= zzz_obj_maru->m_Hit256R;/* ○のあたり判定サイズ */
			uuu = obj_collision_check_00_tama(src, OBJ_Z04_TAMA);/* 弾専用 */
			src->m_Hit256R		= chache_m_Hit256R;/* 戻す */
//			#endif
		#else
			src->m_Hit256R		= TEST_FIX_DEATH001;/* てすと、死亡判定。 */
			/* 自機で判定 */
			uuu = obj_collision_check_00_tama(src, OBJ_Z04_TAMA);/* 弾専用 */
			src->m_Hit256R		= TEST_FIX_GRAZE048;/* てすと、グレイズ判定。 */
		#endif
			if (NULL != uuu)	{	player_set_pichuun();	}
		}
		#endif
	}
}
	/*---------------------------------------------------------
		プレイヤーと敵のあたり判定3(敵専用)
		-------------------------------------------------------
			src 	プレイヤー
			ttt 	敵
		-------------------------------------------------------
		自機が敵(ボス/中型/ザコ)に体当たりされた場合
	---------------------------------------------------------*/
extern void player_weapon_collision_check(OBJ/**/ *shot, int erase_shot_type);
static OBJ_CALL_FUNC(player_collision_check_teki)
{
	#if (1)
	src->m_Hit256R		= TEST_FIX_TEKI001;/* てすと、敵判定。(敵との当たり判定で死ぬ) */
	#endif
	//	static OBJ_CALL_FUNC(player_collision_check_teki)
	{
		OBJ *ttt;	/* 敵自体(ボス/中型/ザコ) */
		/* */  // (OBJ_Z02_TEKI );
		ttt = obj_collision_check_A01_A02_teki(src);// /* 敵専用 */
		if (NULL != ttt)
		{
			if (0 == pds_status_timer)	/* 通常時の場合 */
			{
				player_set_pichuun();
			}
			else
			if (IS_SCENE_DOUCHU_TUIKA)
			/*(ボス中は雑魚追加しない)*/
			/*道中の場合のみ(雑魚追加処理復旧)*/
			{
			//	if (ザコ==ttt)
			//	{
			//		雑魚がダメージを受ける。
					player_weapon_collision_check(src, PLAYER_WEAPON_TYPE_01_BOMB_PLAYER);/* ボム/playerで敵を倒すあたり判定 */
			//	}
			}
		}
	}
}


/*---------------------------------------------------------
	プレイヤー移動
---------------------------------------------------------*/

/*---------------------------------------------------------
	プレイヤーループを抜ける処理
---------------------------------------------------------*/
global void player_loop_quit(void)
{/*(USE_r36_SCENE_FLAG)(??????)*/
	#if (1)
	/* off / 道中コマンド追加読み込み処理を停止する。 */
//	cg.state_flag		&= (~SCENE_NUMBER_MASK);	/*(シーンを消す)*/
//ダメ。理由==continue(?????)	cg.state_flag		&= (0xffff00ffu);	/*(シーンを消す)*/
	cg.state_flag		|= (0x00008000u); //プレイヤーループを抜ける処理(とりあえず)
	#endif
	pds_status_timer	= (LIMIT_m16_GAME_OUT); 	/* とりあえず */	/* 150	 120では若干短い 100 */
}
	#if (0000)
	option[0]->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_00_OPTION_OFF); /* オプションを消す */
	option[1]->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_00_OPTION_OFF); /* オプションを消す */
	option[2]->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_00_OPTION_OFF); /* オプションを消す */
	option[3]->PL_OPTION_DATA_yuukou_flag = (PL_OPTION_FLAG_00_OPTION_OFF); /* オプションを消す */
	#endif/* 0000 */
//	pds_status_timer	= (150);	/* 150	 120では若干短い 100 */
//	cg.special_ivent_type	= PLAYER_STATE_04_GAME_OUT;/* GAME_OUT中 */
	#if (00)
	/* 自機、非表示 */
	/* ○、非表示 */
//	obj_maru->alpha 	= 0x00; 		// ○を消すために入れたけど意味無かったかもしれない。	// ゲームオーバー時の○の表示処理
	#endif
	/* オプションが非表示の場合、何もしない。 */
//	if (PL_OPTION_FLAG_00_OPTION_OFF==(src->PL_OPTION_DATA_yuukou_flag))	{	return; 	}


/*---------------------------------------------------------
	プレイヤー復活処理
---------------------------------------------------------*/

static void player_option_position_init(OBJ *s1)	/* プレイヤー位置の初期化 */
{
	OBJ *option_s1;
	option_s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_04_JIKI_OPTION0];/*(一つ目のオプションにセット。)*/
	unsigned int jj;
	for (jj=0; jj<(OPTION_04_MAX); jj++)
	{
		option_s1->center.x256 = s1->center.x256;/*(自機の座標)*/
		if (PL_OPTION_FLAG_00_OPTION_OFF!=(option_s1->PL_OPTION_DATA_yuukou_flag))	// 可視フラグがOn(可視)なら。
		{	/* オプション登場 */
			option_s1->center.y256 = s1->center.y256;/*(自機の座標)*/
		}
		else	// 可視フラグがOFF(不可視)なら。
		{	/* オプション隠す */
			option_s1->center.y256 = t256(GAME_HEIGHT+1+16);
		}
		option_s1++;/*(次のオプションにセット。)*/
	}
}
static void player_fukkatsu_aaa(OBJ *s1)	/* プレイヤー位置の初期化 */
{
	/* Gu(中心座標) */
	s1->center.x256 						= t256(GAME_WIDTH/2);
	s1->center.y256 						= t256(220);/* 217.6 == (272)GAME_HEIGHT x 0.80 */
	s1->m_zoom.x256 = t256(1.0);/*	初期登場時、拡大率 x 1.0[倍] */
	s1->m_zoom.y256 = t256(1.0);/*	初期登場時、拡大率 x 1.0[倍] */
}

/* ステージ中に復活する場合の無敵設定 */
static void player_few_muteki(void)
{
//	pds_status_timer	= (40); 						// 無敵時間 		/* 120 */ /* 150-120 */
//	cg.special_ivent_type	= PLAYER_STATE_02_SAVE_01;	// 無敵状態？
	pds_status_timer	= (LIMIT_m127_MIN); 			// 無敵時間 		/* 120 */ /* 150-120 */
}

static void player_fukkatsu_bbb222(OBJ *s1)
{
	player_few_muteki();/* ステージ開始時のみ若干の無敵状態にセット */
	#if (00)
	/* 自機、表示 */
	#endif
	/* obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER] */s1->color32	= MAKE32RGBA(0xff, 0xff, 0xff, 0x50);	/* 自機、半透明 */	/*	s1->alpha	= 0x50; */
//
	{
		OBJ *zzz_obj_maru;
		zzz_obj_maru = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
		/* ○、表示 */
		zzz_obj_maru->color32	= MAKE32RGBA(0xff, 0x88, 0x88, 0x50);	/* ○、半透明 */	/*	obj_maru->alpha = 0x50; */
	}
	// チルノAとQの場合、「ボム無し」からスタート.
//	if ((CIRNO_A-1) < cg_game_select_player)/* 6:CIRNO_A or 7:CIRNO_Q (-r34) */
	// チルノAの場合のみ、「ボム無し」からスタート.
	if (CIRNO_A == cg_game_select_player)/* 6:CIRNO_A only. (r35-) */
	{
		cg.bombs			= (0);	/* ボム所持数の初期化 */
	}
	else/* チルノ以外 */
	{
		cg.bombs			= option_config[OPTION_CONFIG_01_BOMB]; 	/* ボム所持数の初期化 */
		/* static_fix_status[BASE_BOMBS+(cg_game_select_player)] */  /* 3 */
	}
	cg.chain_point			= (0);										/* ノーミスボーナスの初期化 */
	// cg.chain_point(ノーミスボーナス)の初期化 // どれだけ連続(ノーミス)でwepon_upを取ったか
//
	check_weapon_level();/* [cg.weapon_powerが変更された場合に必ず行う後チェック] */
}

/* ステージデーター読み込み後の無敵設定 */
global void player_init_stage(void)
{
	OBJ *s1;
	s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	player_fukkatsu_aaa(s1);			/* プレイヤー位置の初期化 */
	player_option_position_init(s1);	/* プレイヤーオプション位置の初期化 */

//	pds_status_timer		= (40); 						// 無敵時間 		/* 120 */ /* 150-120 */
//	cg.special_ivent_type	= PLAYER_STATE_02_SAVE_01;		// 無敵状態？
	pds_status_timer		= (LIMIT_512_STAGE_START);		// ステージ開始時、無敵時間 	/* 120 */ /* 150-120 */
}
/*---------------------------------------------------------
	プレイヤーやられ処理
---------------------------------------------------------*/

static void player_explode(OBJ *s1)
{
	/* アイテムを吐き出す */
	{
		if ((0==cg.zanki)
			/* &&(0==difficulty) */ /* (紅、調べたら難易度に関係なく[F]が出る)	 */
		)
		{
			/* コンティニューの場合(GAME_OUT)easy の場合 */
			/* 無駄に8個吐かせる */
			/* コンティニューの場合easy の場合： (キャッチ出来る数で点数は違うけど、どれか１つキャッチすれば POWER は同じだから) */
		//	item_create_flags_num(s1, (0==difficulty)?(SP_ITEM_02_P128):(SP_ITEM_01_P008), (8), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
			item_create_flags_num(s1, (SP_ITEM_02_P128), (8), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
		}
		else
		{
			/* コンティニューの場合normal以上の場合： FIRE_POWER_G (8) x (8) == 64/128 (全部集めて50%) 。 */
			/* コンティニューの場合(GAME_OUT)normal以上の場合 */
			/* コンティニュー以外の場合 */
			/* 極端に弱くて死んだ場合の救済策:
				  上手い人は(一面)序盤で FULLPOWER になると思うし、
				仮に凡ミスで死んだとしてもボム回収などで POWER を維持するので、
				極端に弱くて死ぬ事はほぼない。
				  極端に弱くて死ぬのは結構下手だと思うので、若干の救済策が必要かと思う。
				その場合 FIRE_POWER_G (8) x (7+1) == 64/128 (全部集めて50%) にした。
			 */
			#if (0)
			/*
				パワーアップシステムを若干見直したので、(30-1) -> (16) へ基準を厳しくした。
 WEAPON_L0(P000-P008)
 WEAPON_L1(P008-P015)
 WEAPON_L2(P016-P031)
 WEAPON_L3(P032-P063)
 WEAPON_L4(P064-P127)
 WEAPON_L5(P128)
					WEAPON_L1以下で死んだ場合のみ救済策があり、
					全部取るとWEAPON_L3になるので、妥当だと思う。が、多少多いかな?
					WEAPON_L1[P15] -> 死ぬ -> 全部取る[P8]x6[個] -> [P15+P8x6]==WEAPON_L3[P63]
					WEAPON_L1[P15] -> 死ぬ -> １つ取る[P8]x1[個] -> [P15+P8x1]==WEAPON_L2[P23]
					WEAPON_L0[P00] -> 死ぬ -> 全部取る[P8]x6[個] -> [P00+P8x6]==WEAPON_L3[P48]
					WEAPON_L0[P00] -> 死ぬ -> １つ取る[P8]x1[個] -> [P00+P8x1]==WEAPON_L1[P08]
					WEAPON_L0[P00] -> 死ぬ -> ３つ取る[P8]x3[個] -> [P00+P8x3]==WEAPON_L2[P24]
					WEAPON_L2[P16] -> 死ぬ -> 全部取る[P1]x6[個] -> [P16+P1x6]==WEAPON_L2[P22]
					死んで半分(3つ)取ると必ずWEAPON_L2以上になる。
			 */
		//	item_create(s1, (((30-1) > cg.weapon_power)?(SP_ITEM_01_P008):(SP_ITEM_00_P001)), (7)/* 5 */, ITEM_MOVE_FLAG_06_RAND_XY);
		//	item_create(s1, (((16) > cg.weapon_power)?(SP_ITEM_01_P008):(SP_ITEM_00_P001)), (6), ITEM_MOVE_FLAG_06_RAND_XY);/* いくら下手でも、多少多いかな? */
		//	item_create(s1, SP_ITEM_01_P008, 1, ITEM_MOVE_FLAG_06_RAND_XY);
			#else
			/* 多少修正してみる */
			item_create_flags_num(s1, (((16) > cg.weapon_power)?(SP_ITEM_01_P008):(SP_ITEM_00_P001)), (3), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );/* 下手な人ががんばれば3つ取れる事が前提 */
			item_create_flags_num(s1, SP_ITEM_00_P001, (5), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );/* P001をばらまく(おまけ、下手な人は、がんばっても同時には取れないという事が前提) */
			#endif
		}
		//
		/* レミリア 特殊能力：抱え落ちすると必ずボムが出る */
		if (REMILIA==(cg_game_select_player))	/* レミリアの場合 */
		{
			/* 抱え落ちすると */
			if (0 != cg.bombs)
			{
				/* 使ってない分の持ってるボムを吐き出す */
				item_create_flags_num(s1, SP_ITEM_04_BOMB, (cg.bombs), (ITEM_MOVE_FLAG_02_WAIT|ITEM_MOVE_FLAG_06_RAND_XY) );
			}
		}
	}
//		cg.explode		= 0;
//	if (0==cg.explode)
	{
	//	bakuhatsu_add_type(t->center.x256+t256(5),t->center.y256+t256(5),/* 0, */BAKUHATSU_MINI00);
	//	t->jyumyou = JYUMYOU_NASI;/* おしまい */			/* あたった敵爆発 */
	//	cg.explode=0;
	//	cg.bonus=0;
		//	voice_play(VOICE04_SHIP_HAKAI, TRACK03_IVENT_DAN/* TR ACK01_PICHUN */);/* 自機死に音は、なるべく重ねない */ // 場所を移動する。// 変更元
		/* 爆発エフェクト */
		/* 自分爆発 */
		#if 1
		set_REG_DEST_XY(s1);/* 発弾位置 座標xy */
		{
			int jj;
			for (jj=0; jj<(4); jj++)
			{
				bakuhatsu_add_type_ccc(BAKUHATSU_MINI00);
			}
		}
		#endif
		/*	 */
		cg.bomber_time	= 0;			/* ←ここが無いせいで魔理沙(&チルノ)ボム撃てなくなってた */
		#if 1
	//	cg.bomber_time = 0;/* 都合上 */
		set_bg_alpha(255);/* 画面を明るくする */
		#endif

	//	cg.state_flag		= JIKI_FLAG_0x00_ALL_OFF;/* ??? */		/*(全フラグを消す特殊機能)*/
		cg.state_flag		&= (~(	JIKI_FLAG_0x0010_JYOU_BU_SYUU_SYUU			|		/* 終わり */
									JIKI_FLAG_0x0020_BOMBER_SYUU_SYUU			|		/* 終わり */
									JIKI_FLAG_0x0040_BOSS_GO_ITEM_JIDOU_SYUU_SYUU));	/* 終わり */
	}
}

/*---------------------------------------------------------
	プレイヤー移動、特殊処理
	-------------------------------------------------------
	やられ中、復活中、ボム中、GAME_OUT中などの特殊処理
	-------------------------------------------------------
	予定:タイマー再設計。

	０以外の場合タイマーは自動で1減算(デクリメント)。
	pds_status_timer--;
	pds_status_timer &= 0xff; // 何らかの値でマスク
//
	負値(-255): LIMIT_m64_MINUS_LIMIT
		復活中							(方向キー入力無効。ボム低速等キー入力、無効)
	負値(-127): LIMIT_m127_MIN
		ゲームオーバーデモ				(方向キー入力無効。ボム低速等キー入力、無効。敵あたり無し。弾あたり無し。)
	負値(-16): LIMIT_m16_GAME_OUT		PLAYER_STATE_04_GAME_OUT判定(-256)。
		喰らいボム受付					(方向キー入力無効。ボム低速等キー入力、有効。敵あたり無し。弾あたり無し。)
		マイナス一定値までは喰らいボム受付時間。弾にあたった場合、キャラ別で初期値(-240とか-200とか)が違う。
	負値(-1): LIMIT_m1_KURAI_BOMB_UKETUKE
		弾にあたった場合、(値を)ワープ
	ZERO(0):	LIMIT_0_ZERO			通常時(pspはZEROレジスタがあるため0比較は速い)
		通常時							(方向キー入力有効。ボム低速等キー入力、有効。敵あたり判定有り。弾あたり判定有り)
	ZERO(0):	LIMIT_0_ZERO			通常時(pspはZEROレジスタがあるため0比較は速い)
	ITI(1): 	LIMIT_1_ONE 			会話動作時(イベント中)
		復活中に付き無敵。				(方向キー入力有効。ボム低速等キー入力、有効。敵あたり無し。弾あたり無し。)
	128?(128):	LIMIT_128				プレイヤー復活時間。(固定?)
		復活中に付き無敵。				(方向キー入力有効。ボム低速等キー入力、有効。敵あたり無し。弾あたり無し。)
	255:
		ゲーム開始時に付き無敵。		(方向キー入力有効。ボム低速等キー入力、有効。敵あたり無し。弾あたり無し。)
	512:
---------------------------------------------------------*/
//void render_continue(void/* int cg_game_now_max_continue */);

static void player_move_special_ivent(OBJ *s1)
{
	pds_status_timer--;
	#if 0
//	pds_status_timer = (signed int)(pds_status_timer & (0x1ff)); // 何らかの値でマスク
	#else
	if (LIMIT_m64_MINUS_LIMIT > pds_status_timer)	{	pds_status_timer += (512); }
//	if (-511 > pds_status_timer)					{	pds_status_timer += 1024; }/* デバッグ検証用 */
	#endif
//
	if (LIMIT_m127_MIN > pds_status_timer)
	{
	//	if (LIMIT_fukki2 == pds_status_timer)
	//	{
	//		;
	//	}
		/* 復活中の処理、拡大してたら X のみ縮小。Y は変更せず。 */
		if (t256(1.0) < s1->m_zoom.x256)
		{
			s1->m_zoom.x256 -= (5*4);// 		s1->m_zoom.x256 -= (5);
		//	s1->m_zoom.y256 -= (5);
		}
		else
		{
			s1->m_zoom.x256 = (t256(1.0));
		//	s1->m_zoom.y256 = (t256(1.0));
		}
	}
	else
	if (LIMIT_m127_MIN == pds_status_timer)
	{
		//ゲームオーバーデモ
//		case PLAYER_STATE_04_GAME_OUT:/* GAME_OUT中 */
//			cg.special_ivent_type	= 0;/* ??? */
			cg.game_now_max_continue--;
			if (
					(0 < cg.game_now_max_continue)
				#if (0)/* (0==DE BUG) */
				/* まだ無効 */
				&& ( (6) != cg.game_now_stage)	/* 最終面はコンティニュー出来ない。 */
				#endif
				)
			{
				cg.player_data_use_continue++;	/* コンティニュー回数 */
			//	render_continue(/* cg_game_now_max_continue */);
				cb.main_call_func = ask_continue_menu_start;
			}
			else
			{
				cb.main_call_func = gameover_start;
			}
//			break;
	}
	else
	if (LIMIT_m16_GAME_OUT > pds_status_timer)
	{
		;/* [なにもしない] */
		/* (ミス確定してから)ゲームアウトになるまでの猶予時間 */
		/* (自分のアイテムが飛び散る時間) */
	}
	else
	if (LIMIT_m16_GAME_OUT == pds_status_timer) /* プレイヤー、ガッツ減少処理 */
	{
		/* 現在オプション増えすぎて、後半重くなるバグがある。 */
		#if (0000)
		option[0]->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_00_OPTION_OFF);	/* オプションを消す */
		option[1]->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_00_OPTION_OFF);	/* オプションを消す */
		option[2]->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_00_OPTION_OFF);	/* オプションを消す */
		option[3]->PL_OPTION_DATA_yuukou_flag	= (PL_OPTION_FLAG_00_OPTION_OFF);	/* オプションを消す */
		#endif/* 0000 */
		cg.player_data_count_miss++;	/* ミス回数 */
		/*(ゲームランクを下げる)*/
		cg.game_rank >>= 1;
		/* 残チャンス減らす */
		cg.zanki--;
		if (0 > cg.zanki)	/* 残チャンスがなければ */
		{
			player_loop_quit();
		}
		else
		{
		/*	MAX(128)->死ぬ->(112)->死ぬ->(96)->死ぬ->(80)->死ぬ->(64)	(常に16減で一定)	 */
			cg.weapon_power -= (16);	/* 武器レベルの低下(紅、調べたら難易度に関係なくP16減だった) */
			#if (0)
			if (0 > cg.weapon_power)	{	cg.weapon_power = 0;	}
			#else/*(ok?)*/
			cg.weapon_power = psp_max(cg.weapon_power, (0));
			#endif
			player_fukkatsu_aaa(s1);	/* プレイヤー位置の初期化 */
			player_fukkatsu_bbb222(s1);
			s1->m_zoom.x256 = t256(1.0)+(120*5);/* 拡大 */
			s1->m_zoom.y256 = t256(1.0);//+(120*5);/* 拡大 */
		}
	}
	else
	if (LIMIT_m1_KURAI_BOMB_UKETUKE > pds_status_timer)
	{
		;/* [なにもしない] */
		/* 喰らいボム受付の猶予時間 */
		//喰らいボム受付中の処理
//		case PLAYER_STATE_01_KURAI_BOMB_UKETUKE:/* 喰らいボム受付中 */
//			/* 死亡確定 */
//			break;
	}
	else
	/*
		(LIMIT_1_ONE-1)はつまり 現状 値(0) だけど、意味は(LIMIT_1_ONE-1)という意味。
		(LIMIT_1_ONEから 1 引いたもの、この 値(-1) は(player_move_special_ivent();開始時の)pds_status_timer--;を補正する分。)
		(結果的に(現在は)LIMIT_0_ZEROと同じだが、意味はLIMIT_0_ZEROと同じではない。)
		LIMIT_1_ONEは固定値(1)ではない、現状 値(1) だけど将来は判らない。
		 */
	if ((LIMIT_1_ONE-1) == pds_status_timer)
	{
		/* 半透明を通常に戻す */
		s1->color32 		= MAKE32RGBA(0xff, 0xff, 0xff, 0xff);				/*	s1->alpha			= 0xff; */
		{
			OBJ *zzz_obj_maru;
			zzz_obj_maru = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU];
			zzz_obj_maru->color32	= MAKE32RGBA(0xff, 0x88, 0x88, 0xee);		/* ○、 */	/*	zzz_obj_maru->alpha = 0xff; */
		}
		/*(アイテム自動収集フラグを戻す)*/
		{
			/* 自動収集モードフラグを全て消す。 */
			cg.state_flag &=
			(	~(	JIKI_FLAG_0x0010_JYOU_BU_SYUU_SYUU				|	/* MAX時の上回収 */
					JIKI_FLAG_0x0020_BOMBER_SYUU_SYUU				|	/* ボム発動中のみ回収 */
					JIKI_FLAG_0x0040_BOSS_GO_ITEM_JIDOU_SYUU_SYUU		/* ボス撃破時の一時回収 */
				)
			);
		}
	}
//	else
//	if ((LIMIT_128-1) == pds_status_timer)
//	{
//		case PLAYER_STATE_03_SAVE_02:/* プレイヤー復活中２ */
//			cg.special_ivent_type	= PLAYER_STATE_00_NORMAL;
//			s1->m_zoom.x256 		= t256(1.0)+100;	 /* サイズ */
//			break;
//	}
}


/*---------------------------------------------------------
	プレイヤー移動、メイン処理
	-------------------------------------------------------
	ボスでボム中無敵
	ボム中は、ボス / 中ザコ敵 にあたって死ぬ
	会話モード動作中 は、敵あたり判定はない
	キー入力無効中(==復活中) は、敵あたり判定はない
	ボム中は、 ボス/ザコ敵 にあたって死なない
	喰らいボム受付中 は、敵あたり判定はない
---------------------------------------------------------*/

static void any_player_move(OBJ *s1)
{
	cg.state_flag &= (~JIKI_FLAG_0x0080_SHOT_KEY_SEND_FOR_OPTION);	/* off(オプションがショットを撃つのを止める) */
	if (IS_SCENE_KAIWA_MODE)
	{
		pds_status_timer = (LIMIT_1_ONE);	/* 会話モード動作中 は 1 */
	}
	/* LIMIT_m16_GAME_OUTより大きい場合、移動可能、ボタン受け付け可能 */
	if (LIMIT_m16_GAME_OUT < pds_status_timer)
	{
		player_keycontrol(s1);/* 移動＋ボタン処理 */
	}
	/* 通常時 又は 例外時の処理。(例外時の処理は分離しとく) */
	if (0 == pds_status_timer)	/* 通常時の場合 */
	{
		/* プレイヤーと、「敵弾によるグレイズ」/「敵弾による死亡」の当たり判定 */
		player_collision_check_tama(s1);
		{
			/* [0] ゲームランクを上げる。 */
			cg.game_rank++;
			cg.game_rank = psp_min(cg.game_rank, 65535);/*(最大ランク)*/
			#if (0)/*デバッグ用(スコア欄にゲームランクを表示)*/
			cg.game_score	= cg.game_rank;
			#endif
		}
	}
	else	/* 例外時(特殊処理)の場合 */
	{
		player_move_special_ivent(s1);	/* 特殊処理 */
	}
	/*(敵の場合)*/
//	if (0 == pds_status_timer)	/* 通常時の場合 */
	#if (1)
	if (IS_SCENE_KAIWA_TATAKAU)
	#endif
	{
		/*(会話シーンで自機死亡のあたり判定を取らない。)*/
		/* プレイヤーと、「敵(雑魚＆ボス)による死亡」の当たり判定 */
		/*(道中通常時、自機vsボスで、自機死ぬ判定)*/		/*(必要)[通常時には体当たりで喰らいボム受け付け状態へ移行する]*/
		/*(道中通常時、自機vs雑魚で、自機死ぬ判定)*/		/*(必要)[通常時には体当たりで喰らいボム受け付け状態へ移行する]*/
		/*(道中無敵時、自機vsボスで、ボス死ぬ判定)*/		/*(要デバッグ)*/
		/*(道中無敵時、自機vs雑魚で、雑魚死ぬ判定)*/		/*(必要)[道中無敵時には体当たりで雑魚を倒す事が出来る。]*/
		/*(会話イベント無敵時、自機vsボスで、ボス死なない)*/	/*(？)*/
		/*(会話イベント無敵時、自機vs雑魚で、雑魚死なない)*/	/*(必要)[会話イベント無敵時には体当たりで雑魚を倒す事が出来ない。]*/
		player_collision_check_teki(s1);
	}
	/* アイテムは常に取れる */
	player_collision_check_item(s1);		/* アイテムの当たり判定 */
}

//	bullets_to_hosi();/* 弾全部、星アイテムにする */
//	if (0 <= pds_status_timer)	/* 正値の場合、移動可能 */

	#if 0/* デバッグ */
	if (0 <= pds_status_timer)	/* 正値の場合 */
	{
		p d_my_score	= pds_status_timer;
		p d_graze_point = 0;
	}
	else
	{
		p d_my_score	= -pds_status_timer;
		p d_graze_point = 11;
	}
	#endif


/*---------------------------------------------------------
	プレイヤー初期化()
---------------------------------------------------------*/
#if (1==USE_EXTEND_CHECK)
extern void player_init_extend_score(void);
#endif
//extern int zanki;
global void player_continue_value(void)
{
	cg.zanki							= (1+option_config[OPTION_CONFIG_00_PLAYER]);
	cg.game_score						= score(0);
	#if (1==USE_EXTEND_CHECK)
	player_init_extend_score();
	#endif
	OBJ *s1;
	s1 = &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER];
	player_fukkatsu_aaa(s1);	/* プレイヤー位置の初期化 */
	player_fukkatsu_bbb222(s1);/* オプションを追加より後 */

	/*
		[コンティニュースタート時]及び、[新規スタート時]の特別処理。(つまりゲーム中復活時[以外の]場合)
		------------------------------------------------------------
		これらの場合は、選択後に無敵になり、
		かつ直ぐに動ける(方向キー入力有効...)ように細工する。
		------------------------------------------------------------
		(ゲーム中復活時の場合は一定時間動けない。)
	 */
	/* 拡大率を1.0倍にする。 */
//	s1->m_zoom.x256 = (t256(1.0));
	/* (無敵時間で)直ぐに動ける。 */
	pds_status_timer = (LIMIT_300_CONTINUE);
}

/*---------------------------------------------------------
	プレイヤー自機を作成。
		FIX_OBJ_00_PLAYER
		FIX_OBJ_01_JIKI_MARU
		FIX_OBJ_02_BOMBER_HONTAI
	//	FIX_O_BJ_03_SEND2
	自機オプションを作成。
		FIX_OBJ_04_JIKI_OPTION0
		FIX_OBJ_05_JIKI_OPTION1
		FIX_OBJ_06_JIKI_OPTION2
		FIX_OBJ_07_JIKI_OPTION3
---------------------------------------------------------*/
extern int jiki_shot_get_player_graze_hankei(void);
static void jiki_create(void)
{
	#if 1
	OBJ *s1;/*(プレイヤー自機本体)*/
	s1					= obj_regist_direct_number(OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_00_PLAYER); /* 必ず登録できる。 */
	s1->jyumyou 		= JYUMYOU_MUGEN;/* 時間で自動消去しない */
	s1->obj_type_set	= (OBJ_Z01_JIKI_GET_ITEM);
	s1->m_Hit256R		= ((jiki_shot_get_player_graze_hankei())<<8);/* グレイズ判定。取得値は[pixel]なので、256倍してt256()形式に変換。 */
	s1->atari_hantei	= (1/*スコア兼用*/);		/* あたり判定のON==(1)==自機が無敵の場合に雑魚に対する強さ。 */
	s1->callback_mover	= any_player_move;
	#endif
//
	#if 1
	OBJ *s2;/* プレイヤー、生死判定用コア(obj_maru == ○)の追加 */
	s2					= obj_regist_direct_number(OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_01_JIKI_MARU); /* 必ず登録できる。 */
	s2->jyumyou 		= JYUMYOU_MUGEN;/* 時間で自動消去しない */
//	s2->obj_type_set	= (JIKI_CORE_00_REIMU_A+(cg_game_select_player));
//	s2->obj_type_set	= (SPELL_SQUERE_);
	s2->obj_type_set	= (SP_DUMMY_MUTEKI);/*(とりあえず表示しない)*/
	s2->m_Hit256R		= t256(1.0);/*(半径1[pixel]==直径2[pixel]の円で判定)*/
	#endif
//
	#if 1
	OBJ *s3;/* プレイヤー、ボンバー本体の追加 */
	s3					= obj_regist_direct_number(OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_02_BOMBER_HONTAI); /* 必ず登録できる。 */
	s3->jyumyou 		= JYUMYOU_MUGEN;/* 時間で自動消去しない */
//	s3->obj_type_set	= (JIKI_CORE_00_REIMU_A+(cg_game_select_player));
//	s3->obj_type_set	= (SPELL_SQUERE_);
	s3->obj_type_set	= (SP_DUMMY_MUTEKI);/*(とりあえず表示しない)*/
//	s3->atari_hantei	= (0/*スコア兼用*/);		/* あたり判定のOFF==(0) */
	s3->m_Hit256R		= (0);
	#endif
//
	#if 1
	OBJ *s4;/* プレイヤー、低速effect本体の追加 */
	s4					= obj_regist_direct_number(OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_15_JIKI_TEISOKU_EFFECT); /* 必ず登録できる。 */
	s4->jyumyou 		= JYUMYOU_MUGEN;/* 時間で自動消去しない */
//	s4->obj_type_set	= (JIKI_CORE_00_REIMU_A+(cg_game_select_player));
//	s4->obj_type_set	= (SPELL_SQUERE_);
	s4->obj_type_set	= (SP_DUMMY_MUTEKI);/*(とりあえず表示しない)*/
	s4->atari_hantei	= (0/*スコア兼用*/);		/* あたり判定のOFF==(0) */
	s4->m_Hit256R		= (0);
	#endif

//	#define TEISOKU_EFFECT_00_OBJ (6)
//	#define TEISOKU_EFFECT_01_OBJ (7)
	#if 0
	s4					= &obj99[OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_15_JIKI_TEISOKU_EFFECT];
	s4->atari_hantei	= ATARI_HANTEI_OFF; 		/* あたり判定のOFF(無敵) */ /* あたり判定無し */
	s4->color32 		= MAKE32RGBA(0xff, 0x22, 0x22, 0x80);	/* 自機、半透明 */	/*	s1->alpha			= 0x50;*/
	#endif
}
	//	s1->m_Hit256R		= JIKI_ATARI_ITEM_16;/* t256(16.0); グレイズ判定 */
	//	s1->m_Hit256R		= graze_atari[(cg_game_select_player)];/* グレイズ判定 */

/*---------------------------------------------------------
	プレイヤー初期化。
---------------------------------------------------------*/
extern void jiki_option_create(void);

/*static*/extern void kaiwa_init_obj_position(void);/*(r35u2とりあえず)*/
global void obj_initialize_one(OBJ *obj);
extern void init_player_shot(void);
extern void select_jiki_load_surface(void);
extern void obj_system_init(void);
global void jiki_class_initialize(void)
{
	select_jiki_load_surface();
	obj_system_init();/*(スプライトオブジェクト システム初期化)*/
	obj_system_cleanup_all();/* [A00弾領域]と[A01固定敵領域]と[A02敵領域]と[A03固定領域]と[A04パネル領域]のOBJを全消去。 */
	//
	unsigned int ii;
	for (ii=0; ii<OBJ_POOL_04_PANEL_0056_MAX; ii++)/* 全部 */
	{
		OBJ *obj;/* 初期化するスプライト */
		obj = &obj99[OBJ_HEAD_04_0x0a10_PANEL+ii];
		obj_initialize_one(obj);/* 1枚のスプライトオブジェクトを初期化 */
	}
	unsigned int kk;
	#define PPP (GAME_WIDTH)
	kk = ((PPP+5*8+4)<<8);
//	unsigned int jj;
//	for (jj=0; jj<(2); jj++)/* */
	for (ii=0; ii<(10); ii++)/* */
	{
		OBJ *obj;/* 初期化するスプライト */
		/* スコア */
		obj = &obj99[OBJ_HEAD_04_0x0a10_PANEL+ii+PANEL_OBJ_00_S00];
		obj->center.x256 = (kk);
		obj->center.y256 = ((6*8+7)<<8);
		/* ハイスコア */
		obj = &obj99[OBJ_HEAD_04_0x0a10_PANEL+ii+PANEL_OBJ_10_H00];
		obj->center.x256 = (kk);
		obj->center.y256 = ((3*8+2)<<8);
		//
		kk += (8*256);
	}
	//----[BOSS]	/* ボス本体 を作成 */
	/* あたり判定の都合上 */
	{	OBJ *b1;
	//	b1								= obj_regist_teki();	/* 敵obj番号の0番を必ず取得できる。 */
		/*(あたり判定の都合上、[A02固定領域]には登録できない。[A01敵領域]に登録する必要がある。)*/
		b1								= obj_regist_direct_number(OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS00_HONTAI); /* 必ず登録できる。 */
	//	b1 = &obj99[OBJ_HEAD_02_0x0900_TEKI_FIX+TEKI_OBJ_00_BOSS_HONTAI];
		#if (0)/*(無くても可)*/
		b1->obj_type_set				= BOSS_00_11;//???
		#endif
	//重複	b1->jyumyou 					= (JYUMYOU_MUGEN);/* 時間で自動消去しない */	/*(固定確保で判別されるフラグ)*/
		sprite_kotei_obj_r36_taihi(b1);/*(ボスobj使用中であるが退避位置へ退避)*/
	}
	//----[EFFECT]	/* ボスeffect を作成 */
	{
		{	unsigned int i;
			for (i=0; i<(5+3/*+3*/); i++)
			{
				OBJ *h;
				h						= obj_regist_direct_number(OBJ_HEAD_03_0x0a00_KOTEI+FIX_OBJ_08_EFFECT01+i); /* 必ず登録できる。 */
				h->obj_type_set 		= (SPELL_SQUERE_);
		//重複	h->jyumyou				= JYUMYOU_MUGEN;/* 時間で自動消去しない */
		//重複	h->atari_hantei 		= ATARI_HANTEI_OFF; 		/* あたり判定無し */
			}
		}
		boss_effect_kotei_obj_r36_taihi();
	}
	//
	jiki_create();			/* 自機 を作成 */
	jiki_option_create();	/* 自機オプションを作成 */
	//
	cg.player_data_use_continue 		= 0;	/* コンティニュー回数 */
	cg.player_data_count_miss			= 0;	/* ミス回数 */
	cg.player_data_used_bomber			= 0;	/* ボム使用回数 */
	cg.player_data_use_kurai_bomb		= 0;	/* 喰らいボム使用回数 */
//	cg.player_data_count_bonus			= 0;	/* カードボーナス回数 */
//
	cg.bomber_time						= 0;	/* ==bomb_wait */
	cg.graze_point						= 0;
	cg.game_rank						= 0;	/* ゲームランク */
//
	/* (r32) */cg.state_flag			= JIKI_FLAG_0x00_ALL_OFF;/*(全フラグを消す特殊機能)*/
//
	card.boss_hp_dec_by_frame			= 0;/* ボス攻撃減少値、フレーム単位 */
//
//	cg.jiki_weapon_level_offset 		= (cg_game_select_player) + (/* 0==武器レベル */0<<3);
	cg.jiki_weapon_level				= (/* 0==武器レベル */0<<3);/*(r35u2)*/
	/* 練習モードの場合はフルパワーで始める(その代わりクリア後のイベントが見れない) */
	cg.weapon_power 					= (0==cg.game_practice_mode)?(0):(MAX_POWER_IS_128);
//
	cg.game_now_max_continue			= DEFAULT_MAX_CONTINUE;/* (3) */
	cg.chuu_boss_mode					= (0);/* どこかで初期化が必ず必要 */
	init_player_shot();/*(ショットの性能をプレイヤー別に初期化)*/
	#if 1
	player_continue_value();
	#endif

	#if 1/* (r33仕様変更により)どこかで初期化が必ず必要(ここでない方が良いかも？) */
	HATSUDAN_04_tama_spec				= (DANMAKU_LAYER_00)|(0);/* どこかで初期化が必ず必要 */
	#endif

	#if 1/*(r35u2とりあえず)*/
	{
		kaiwa_init_obj_position();
	}
	#endif
}


/*---------------------------------------------------------
	敵やられ
	ボス倒した場合の処理
	(プレイヤー側含む)
	-------------------------------------------------------
	ボスを倒した場合に、プレイヤーが一時的に無敵になる。
	この処理の為ボスを倒した場合にここが直ぐに呼ばれる。
	-------------------------------------------------------
	(他の方式として、フラグの特殊イベントにして対処する方法もある。)
---------------------------------------------------------*/
global void jiki_eien_muteki_on(void)
{
//	cg.special_ivent_type	= PLAYER_STATE_02_SAVE_01;	// 無敵状態？
//	cg.special_ivent_type	= PLAYER_STATE_03_SAVE_02;	/* 稀に、うまくいかない */
	/*
		無敵時間 ボス倒したら一時的に、永遠(18.5分)に無敵にする。
		この無敵は、次のステージが始まる場合に解除される。
	*/
	pds_status_timer		= (LIMIT_65535_BOSS_TAOSITA);
}
