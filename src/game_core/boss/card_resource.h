
/*---------------------------------------------------------
	カード設定。
---------------------------------------------------------*/

typedef struct
{
	int spell_life; 							/* カードに登録された一定体力 */
	int spell_limit_time;						/* カードの制限時間。(カードに登録された一定時間) */
//
	const char *spell_str_name; 				/* カード名称 */
	int spell_set_number;						/* カードの種類 */
//	/*(r36, NULLは登録できない。何もしない場合は NULL_keitai を登録する。)*/
	void (*spell_init_callback)(OBJ *sss);				/* 初期化移動処理 */
	void (*boss_move_keitai_set_callback)(OBJ *sss);	/* ボス移動形態選択処理 */
	#if 0
	int spell_bonus_score;		/* カードを取得した場合に得られる得点。(20万〜80万程度を想定。) */
	int spell_bonus_item;		/* カードを取得した場合に得られるITEM。(倒すと1up出すが、時間切れだと無しとかを設定。) */
	#endif
} CARD_ADDRESS_RESOURCE;

/* カード時間(==単位[フレーム])は、64倍(==単位[約1秒])が規格 */
#define s_time(aaa) (((int)(aaa))<<6)

/* ボス体力単位は、1024倍を単位にしてみる(-r35u1) */
//#define s_hp(aaa) (((int)(aaa))<<10)

/* ボス体力単位は、4096倍を単位にしてみる(r35u2-) */
#define s_hp(aaa) (((int)(aaa))<<12)

#if 0
	// 32でゲージ1本(r32)
	32768==1024*32==s_hp(32)
//
311296==32768*9.5
294912==32768*9.0
262144==32768*8.0
237568==32768*7.25
229376==32768*7.0
196608==32768*6.0
163840==32768*5.0
147456==32768*4.5
131072==32768*4.0
114688==32768*3.5
98304==32768*3.0
81920==32768*2.5
65536==32768*2.0
49152==32768*1.5
#endif


/* 註: 符名はテキトーです。 */

/*---------------------------------------------------------
	氷符「アイシクルフォール」動かないでカードを撃つ。
---------------------------------------------------------*/

static CARD_ADDRESS_RESOURCE my_card_resource[CARD_ADDRESS_MAX] __attribute__((aligned(32))) =
{											// 最大半角で30文字。
// チルノ エキストラステージ				"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*5+32*3.5),	s_time(900),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*5+32*3.5),	s_time(900),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
//	3.5
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_10_cirno, 					NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第一形態: " */	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_10_cirno, 					NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第一形態: " */	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_10_cirno, 					NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第一形態: " */	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_10_cirno, 					NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第一形態: " */	/* 初回の攻撃分(手動設定)  500 160	*/
//	3.0
	{	s_hp(28),		s_time(60), 		"　　氷符「アイシクルフォール」" "\n",	SPELL_1b_cirno_icecle_fall, 		init_00_boss_clip222,		boss_move_01_taihi_ue_naka, 			},	/* "第二形態: " */
	{	s_hp(28),		s_time(60), 		"　　氷符「アイシクルフォール」" "\n",	SPELL_1b_cirno_icecle_fall, 		init_00_boss_clip222,		boss_move_01_taihi_ue_naka, 			},	/* "第二形態: " */
	{	s_hp(28),		s_time(60), 		"　　氷符「アイシクルフォール」" "\n",	SPELL_1b_cirno_icecle_fall, 		init_00_boss_clip222,		boss_move_01_taihi_ue_naka, 			},	/* "第二形態: " */
	{	s_hp(28),		s_time(60), 		"　　氷符「アイシクルフォール」" "\n",	SPELL_1b_cirno_icecle_fall, 		init_00_boss_clip222,		boss_move_01_taihi_ue_naka, 			},	/* "第二形態: " */
//	2.25
	{	s_hp(12),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_0c_sakuya_jack32, 			init_00_boss_clip000,		boss_move_02_xy_hidouki,				},	/* "第三形態: " */
	{	s_hp(12),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_0c_sakuya_jack32, 			init_00_boss_clip000,		boss_move_02_xy_hidouki,				},	/* "第三形態: " */
	{	s_hp(12),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_0c_sakuya_jack32, 			init_00_boss_clip000,		boss_move_02_xy_hidouki,				},	/* "第三形態: " */
	{	s_hp(12),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_0c_sakuya_jack32, 			init_00_boss_clip000,		boss_move_02_xy_hidouki,				},	/* "第三形態: " */
//	2.0
	{	s_hp(20),		s_time(24), 		"　凍符「パーフェクトフリーズ」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第四形態: " */
	{	s_hp(20),		s_time(24), 		"　凍符「パーフェクトフリーズ」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第四形態: " */
	{	s_hp(20),		s_time(24), 		"　凍符「パーフェクトフリーズ」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第四形態: " */
	{	s_hp(20),		s_time(24), 		"　凍符「パーフェクトフリーズ」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第四形態: " */
//	1.5
	{	s_hp(64),		s_time(60), 		"雪符「ダイアモンドブリザード」" "\n",	SPELL_12_diamond_blizzard,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(64),		s_time(60), 		"雪符「ダイアモンドブリザード」" "\n",	SPELL_12_diamond_blizzard,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(64),		s_time(60), 		"雪符「ダイアモンドブリザード」" "\n",	SPELL_12_diamond_blizzard,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(64),		s_time(60), 		"雪符「ダイアモンドブリザード」" "\n",	SPELL_12_diamond_blizzard,			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//	0.0
//----------------------------------------
	// 咲夜easyは短い上に段階が少ない。
// 咲夜 6面 								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*12+32*2.0),s_time(900), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5),s_time(900), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5),s_time(900), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
	{s_hp(4*12+32*3.5),s_time(900), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},	/* 73728==8192*9.0 */
//	9.5
	{	s_hp(10),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_01_sakuya_misogi_normal,		NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第一形態: 通常攻撃(左右に動いて禊弾撃ち)"		*/	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_01_sakuya_misogi_normal,		NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第一形態: 通常攻撃(左右に動いて禊弾撃ち)"		*/	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_01_sakuya_misogi_normal,		NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第一形態: 通常攻撃(左右に動いて禊弾撃ち)"		*/	/* 初回の攻撃分(手動設定)  500 160	*/
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_2d_sakuya_misogi_lunatic, 	NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第一形態: 通常攻撃(左右に動いて禊弾撃ち)"		*/	/* 初回の攻撃分(手動設定)  500 160	*/
//	9.0
	{	s_hp(9),		s_time(16), 		"　　奇術「ミスディレクション」" "\n",	SPELL_0d_sakuya_miss_direction, 	NULL_keitai,				boss_move_14_sakuya_miss_direction, 	},	/* "第二形態: 奇術「ミスディレクション」(全方位、豆まき)"	*/
	{	s_hp(10),		s_time(16), 		"　　奇術「ミスディレクション」" "\n",	SPELL_0d_sakuya_miss_direction, 	NULL_keitai,				boss_move_14_sakuya_miss_direction, 	},	/* "第二形態: 奇術「ミスディレクション」(全方位、豆まき)"	*/
	{	s_hp(11),		s_time(16), 		"奇術「幻惑ミスディレクション」" "\n",	SPELL_0d_sakuya_miss_direction, 	NULL_keitai,				boss_move_14_sakuya_miss_direction, 	},	/* "第二形態: 奇術「ミスディレクション」(全方位、豆まき)"	*/
	{	s_hp(11),		s_time(16), 		"奇術「幻惑ミスディレクション」" "\n",	SPELL_0d_sakuya_miss_direction, 	NULL_keitai,				boss_move_14_sakuya_miss_direction, 	},	/* "第二形態: 奇術「ミスディレクション」(全方位、豆まき)"	*/
//	8.25	// bloody==血だらけの。 staind ステインド==ステンド==(色を)焼き付け(て残す)る。
	{	s_hp(7),		s_time(20), 		NULL,/* "通常攻撃3" "\n"*/				SPELL_2c_sakuya_blue_red,			NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第三形態: " */
	{	s_hp(8),		s_time(20), 		NULL,/* "通常攻撃3" "\n"*/				SPELL_2c_sakuya_blue_red,			NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第三形態: " */
	{	s_hp(8),		s_time(20), 		NULL,/* "通常攻撃"螺旋赤ナイフ */		SPELL_4d_remilia_rasen_knife,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* "第三形態: (テスト)" */
	{	s_hp(8),		s_time(20), 		NULL,/* "通常攻撃"螺旋赤ナイフ */		SPELL_4d_remilia_rasen_knife,		NULL_keitai,				boss_move_04_xy_douki_differential32,	},	/* "第三形態: (テスト)" */
//	8.0
	{	s_hp(10),		s_time(20), 		NULL,/* "通常攻撃"白緑弾 */ 			SPELL_2a_sakuya_baramaki1,			init_set_dolls_sakuya_T05,	boss_move_04_xy_douki_differential32,	},	/* "第四形態: " */
	{	s_hp(13),		s_time(20), 		NULL,/* "通常攻撃"白緑弾 */ 			SPELL_2a_sakuya_baramaki1,			init_set_dolls_sakuya_T05,	boss_move_04_xy_douki_differential32,	},	/* "第四形態: " */
	{	s_hp(13),		s_time(20), 		NULL,/* "通常攻撃"白緑弾 */ 			SPELL_2a_sakuya_baramaki1,			init_set_dolls_sakuya_T05,	boss_move_04_xy_douki_differential32,	},	/* "第四形態: " */
	{	s_hp(13),		s_time(20), 		NULL,/* "通常攻撃"白緑弾 */ 			SPELL_2a_sakuya_baramaki1,			init_set_dolls_sakuya_T05,	boss_move_04_xy_douki_differential32,	},	/* "第四形態: " */
//	7.5 	// meek==素直。Vlad Draculea. Vlad Tepes.
	{	s_hp(12),		s_time(44), 		"呪詛「レッドツェペリンの呪い」" "\n",	SPELL_4e_remilia_vlad_tepes,		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(15),		s_time(44), 		"呪詛「ブラドツェペシュの呪い」" "\n",	SPELL_4e_remilia_vlad_tepes,		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(15),		s_time(44), 		"祝詛「ブラドツェペシュの祝い」" "\n",	SPELL_4e_remilia_vlad_tepes,		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	{	s_hp(15),		s_time(44), 		"恐詛「ブラドツェペシュの恐い」" "\n",	SPELL_4e_remilia_vlad_tepes,		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第五形態: " */
	//
	{	s_hp(19),		s_time(66), 		"　　　　　　「レッドスネーク」" "\n",	SPELL_4f_remilia_red_magic, 		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第六形態: " */
	{	s_hp(22),		s_time(66), 		"　　　　　　「レッドマジック」" "\n",	SPELL_4f_remilia_red_magic, 		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第六形態: " */
	{	s_hp(22),		s_time(66), 		"　　　　　　「レッドマリック」" "\n",	SPELL_4f_remilia_red_magic, 		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第六形態: " */
	{	s_hp(22),		s_time(66), 		"　　　　　　「レッドマジシヌ」" "\n",	SPELL_4f_remilia_red_magic, 		NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第六形態: " */
//	6.5 	// ジャック・ザ・リッパー==Jack the Ripper==切り裂きジャック(殺人鬼)19世紀(1888年)に実在(?)/抽象名詞化。ワールドヒーローズ。 リック==スプラッターハウス
	{	s_hp(16),		s_time(24), 		"　奇抜「ジャック・ガーリック」" "\n",	SPELL_0c_sakuya_jack32, 			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第七形態: (分散魔方陣)追加計画中"		*/
	{	s_hp(20),		s_time(24), 		"奇術「ジャック・ザ・ラッパー」" "\n",	SPELL_0c_sakuya_jack32, 			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第七形態: (分散魔方陣)追加計画中"		*/
	{	s_hp(20),		s_time(24), 		"奇術「ジャック・ザ・ビーンズ」" "\n",	SPELL_0c_sakuya_jack32, 			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第七形態: (分散魔方陣)追加計画中"		*/
	{	s_hp(20),		s_time(24), 		"夢違「ジャック・デ・マメマキ」" "\n",	SPELL_0c_sakuya_jack32, 			NULL_keitai,				boss_move_02_xy_hidouki,				},	/* "第七形態: (分散魔方陣)追加計画中"		*/
//
	{	s_hp(12),		s_time(20), 		NULL,									SPELL_2b_sakuya_baramaki2,			init_set_dolls_sakuya_T06,	boss_move_04_xy_douki_differential32,	},	/* "第八形態: 魔方陣生成"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_2b_sakuya_baramaki2,			init_set_dolls_sakuya_T06,	boss_move_04_xy_douki_differential32,	},	/* "第八形態: 魔方陣生成"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_2b_sakuya_baramaki2,			init_set_dolls_sakuya_T06,	boss_move_04_xy_douki_differential32,	},	/* "第八形態: 魔方陣生成"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_2b_sakuya_baramaki2,			init_set_dolls_sakuya_T06,	boss_move_04_xy_douki_differential32,	},	/* "第八形態: 魔方陣生成"	*/
//	4.5
	{	s_hp(12),		s_time(44), 		"　幻想「フェスティバルナイフ」" "\n",	SPELL_47_sakuya_festival_knife, 	NULL_keitai,				boss_move_15_sakuya_festival_knife, 	},	/* "第九形態: 最終形態(その1)"				*/
	{	s_hp(16),		s_time(44), 		"　幻葬「フェスティバルナイフ」" "\n",	SPELL_47_sakuya_festival_knife, 	NULL_keitai,				boss_move_15_sakuya_festival_knife, 	},	/* "第九形態: 最終形態(その1)"				*/
	{	s_hp(16),		s_time(44), 		"　幻奏「フェスティバルナイフ」" "\n",	SPELL_47_sakuya_festival_knife, 	NULL_keitai,				boss_move_15_sakuya_festival_knife, 	},	/* "第九形態: 最終形態(その1)"				*/
	{	s_hp(16),		s_time(44), 		"　幻騒「フェスティバルナイフ」" "\n",	SPELL_47_sakuya_festival_knife, 	NULL_keitai,				boss_move_15_sakuya_festival_knife, 	},	/* "第九形態: 最終形態(その1)"				*/
//	2.5
	{	s_hp(12),		s_time(20), 		NULL,									SPELL_0e_remilia_00,				NULL_keitai,				boss_move_16_sakuya_nazo_keitai,		},	/* "第10形態: 最終形態(その2)"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_0e_remilia_00,				NULL_keitai,				boss_move_16_sakuya_nazo_keitai,		},	/* "第10形態: 最終形態(その2)"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_0e_remilia_00,				NULL_keitai,				boss_move_16_sakuya_nazo_keitai,		},	/* "第10形態: 最終形態(その2)"	*/
	{	s_hp(16),		s_time(20), 		NULL,									SPELL_0e_remilia_00,				NULL_keitai,				boss_move_16_sakuya_nazo_keitai,		},	/* "第10形態: 最終形態(その2)"	*/
//	0.5
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (easyは一段階少ない。ここで終了する)
	{	s_hp(64),		s_time(66), 		"　　メイド秘密「残虐行為手当」" "\n",	SPELL_0e_remilia_00,				NULL_keitai,				boss_move_17_sakuya_bimyou_idou,		},	/* "第11形態: 最終形態(その3)"				*/
	{	s_hp(64),		s_time(66), 		"　メイド秘宝「あつくて死ぬぜ」" "\n",	SPELL_0e_remilia_00,				NULL_keitai,				boss_move_17_sakuya_bimyou_idou,		},	/* "第11形態: 最終形態(その3)"				*/
	{	s_hp(64),		s_time(66), 		"　　メイド日々「もうすぐボス」" "\n",	SPELL_0e_remilia_00,				NULL_keitai,				boss_move_17_sakuya_bimyou_idou,		},	/* "第11形態: 最終形態(その3)"				*/
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//	0.25

//----------------------------------------
	// パチェeasyは短い上に1段階少ない。
// A(霊符)
// パチェA 5面								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*2.00),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
//	5.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	4.0
	{	s_hp(14),		s_time(30), 		"　　　　火符「アグニシャイン」" "\n",	SPELL_2e_pache_agni_shine_1,		add_laser_off,				boss_move_03_x_douki,					},
	{	s_hp(20),		s_time(30), 		"　　　　火符「アグニシャイン」" "\n",	SPELL_2e_pache_agni_shine_1,		add_laser_off,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　　火符「アグニシャイン上級」" "\n",	SPELL_33_pache_agni_shine_2,		add_laser_off,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　　火符「アグニシャイン上級」" "\n",	SPELL_33_pache_agni_shine_2,		add_laser_off,				boss_move_02_xy_hidouki,				},
//	3.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	2.0
	{	s_hp(14),		s_time(30), 		"　　土符「レイジィトリリトン」" "\n",	SPELL_31_pache_rage_tririton_1, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},/*(テスト)*/
	{	s_hp(20),		s_time(30), 		"土符「レイジィトリリトン上級」" "\n",	SPELL_35_pache_rage_tririton_2, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},/*(テスト)*/
	{	s_hp(20),		s_time(30), 		"　　土符「トリリトンシェイク」" "\n",	SPELL_39_pache_tririton_shake,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},/*(テスト)*/
	{	s_hp(20),		s_time(30), 		"　　土符「トリリトンシェイク」" "\n",	SPELL_39_pache_tririton_shake,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},/*(テスト)*/
//	1.0
	{	s_hp(14),		s_time(30), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
//	0.0
	{	s_hp(14),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
//	0.0
	{	s_hp(64),		s_time(60), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (easyは一段階少ない。ここで終了する)
	{	s_hp(64),		s_time(60), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(64),		s_time(60), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(64),		s_time(60), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//----------------------------------------
// B(夢符)
// パチェB 5面								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*2.00),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
//	5.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	4.0
	{	s_hp(14),		s_time(30), 		"　水符「プリンセスウンディネ」" "\n",	SPELL_2f_pache_princess_undine, 	add_laser_off,				boss_move_04_xy_douki_differential32,	},
	{	s_hp(20),		s_time(30), 		"　水符「プリンセスウンディネ」" "\n",	SPELL_2f_pache_princess_undine, 	add_laser_off,				boss_move_04_xy_douki_differential32,	},
	{	s_hp(20),		s_time(30), 		"　　　水符「ベリーインレイク」" "\n",	SPELL_37_pache_bury_in_lake,		add_laser_off,				boss_move_04_xy_douki_differential32,	},
	{	s_hp(20),		s_time(30), 		"　　　水符「ベリーインレイク」" "\n",	SPELL_37_pache_bury_in_lake,		add_laser_off,				boss_move_02_xy_hidouki,				},
//	3.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	2.0
	{	s_hp(14),		s_time(30), 		"　　木符「シルフィホルン上級」" "\n",	SPELL_34_pache_sylphy_horn_2,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　木符「シルフィホルン上級」" "\n",	SPELL_34_pache_sylphy_horn_2,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　　木符「グリーンストーム」" "\n",	SPELL_38_pache_green_storm, 		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　　木符「グリーンストーム」" "\n",	SPELL_38_pache_green_storm, 		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
//	1.0
	{	s_hp(14),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
//	0.0
	{	s_hp(14),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
//	0.0
	{	s_hp(64),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (easyは一段階少ない。ここで終了する)
	{	s_hp(64),		s_time(60), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(64),		s_time(60), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(64),		s_time(60), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//----------------------------------------
// C(魔符)
// パチェC 5面								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*2.00),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
//	5.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	4.0
	{	s_hp(14),		s_time(30), 		"　　　　木符「シルフィホルン」" "\n",	SPELL_30_pache_sylphy_horn_1,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　　　木符「シルフィホルン」" "\n",	SPELL_30_pache_sylphy_horn_1,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　木符「シルフィホルン上級」" "\n",	SPELL_34_pache_sylphy_horn_2,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　木符「シルフィホルン上級」" "\n",	SPELL_34_pache_sylphy_horn_2,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
//	3.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	2.0
	{	s_hp(14),		s_time(30), 		"　　　　火符「アグニシャイン」" "\n",	SPELL_2e_pache_agni_shine_1,		add_laser_off,				boss_move_03_x_douki,					},
	{	s_hp(20),		s_time(30), 		"　　火符「アグニシャイン上級」" "\n",	SPELL_33_pache_agni_shine_2,		add_laser_off,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　火符「アグニレイディアンス」" "\n",	SPELL_36_pache_agni_radiance,		add_laser_off,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　火符「アグニレイディアンス」" "\n",	SPELL_36_pache_agni_radiance,		add_laser_off,				boss_move_02_xy_hidouki,				},
//	1.0
	{	s_hp(14),		s_time(30), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"木＆火符「フォレストブレイズ」" "\n",	SPELL_3c_pache_forest_blaze,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
//	0.0
	{	s_hp(14),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
//	0.0
	{	s_hp(64),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (easyは一段階少ない。ここで終了する)
	{	s_hp(64),		s_time(60), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(64),		s_time(60), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(64),		s_time(60), 		"火＆土符「ラーヴァクロムレク」" "\n",	SPELL_3b_pache_lava_cromlech,		NULL_keitai,				boss_move_02_xy_hidouki,				},
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//----------------------------------------
// D(恋符)
// パチェD 5面								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*2.00),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
	{s_hp(4*7+32*3.75),s_time(800), 		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 40960==8192*5.0 */
//	5.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_42_PACHE_LASER1,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	4.0
	{	s_hp(14),		s_time(30), 		"　　土符「レイジィトリリトン」" "\n",	SPELL_31_pache_rage_tririton_1, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　土符「レイジィトリリトン」" "\n",	SPELL_31_pache_rage_tririton_1, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"土符「レイジィトリリトン上級」" "\n",	SPELL_35_pache_rage_tririton_2, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"土符「レイジィトリリトン上級」" "\n",	SPELL_35_pache_rage_tririton_2, 	add_laser_off,				boss_move_01_taihi_ue_naka, 			},
//	3.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_43_PACHE_LASER2,				add_laser_on,				boss_move_02_xy_hidouki,				},
//	2.0
	{	s_hp(14),		s_time(30), 		"　　金符「メタルファティーグ」" "\n",	SPELL_32_pache_metal_fatigue,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　金符「メタルファティーグ」" "\n",	SPELL_32_pache_metal_fatigue,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　　金符「シルバードラゴン」" "\n",	SPELL_3a_pache_silver_dragon,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(20),		s_time(30), 		"　　　金符「シルバードラゴン」" "\n",	SPELL_3a_pache_silver_dragon,		add_laser_off,				boss_move_01_taihi_ue_naka, 			},
//	1.0
	{	s_hp(14),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"土＆金符「エメラルドメガリス」" "\n",	SPELL_3f_pache_emerald_megalith,	NULL_keitai,				boss_move_02_xy_hidouki,				},
//	0.0
	{	s_hp(14),		s_time(999/*30*/),	"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(20),		s_time(30), 		"　水＆木符「ウォーターエルフ」" "\n",	SPELL_3d_pache_water_elf,			NULL_keitai,				boss_move_02_xy_hidouki,				},
//	0.0
	{	s_hp(64),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (easyは一段階少ない。ここで終了する)
	{	s_hp(64),		s_time(60), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(64),		s_time(60), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(64),		s_time(60), 		"金＆水符「マーキュリポイズン」" "\n",	SPELL_3e_pache_mercury_poison,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/

//----------------------------------------
//	SPELL_15_aya_misogi
//	SPELL_25_houka_kenran			/*aya_02_keitai*/
//	SPELL_23_meirin_magaru_kunai	/*aya_01_keitai*/

// 文 4面									"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	//																													/*ボス登場前の初期化[会話の前]*/
	{s_hp(4*7+32*3),	s_time(600),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 32768=32768.0 */
	{s_hp(4*7+32*3),	s_time(600),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 32768=32768.0 */
	//	4.0 																											/*ボス戦闘前の初期化[会話の後]*/
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_20_aya_misogi1,				NULL_keitai,				boss_move_03_x_douki,					},/*(4)*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_20_aya_misogi1,				NULL_keitai,				boss_move_03_x_douki,					},/*(4)*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_20_aya_misogi1,				NULL_keitai,				boss_move_03_x_douki,					},/*(4)*/
	{	s_hp(20),		s_time(20), 		NULL,/* "通常攻撃1" "\n"*/				SPELL_20_aya_misogi1,				NULL_keitai,				boss_move_03_x_douki,					},/*(4)*/
	//	3.5
	{	s_hp(22),		s_time(30), 		"　　　　　　　岐符「天の八衢」" "\n",	SPELL_22_ame_no_yatimata,			init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)*/
	{	s_hp(22),		s_time(30), 		"　　　　　　　岐符「天の八衢」" "\n",	SPELL_22_ame_no_yatimata,			init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)*/
	{	s_hp(22),		s_time(30), 		"　　　　　　　岐符「天の八衢」" "\n",	SPELL_22_ame_no_yatimata,			init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)*/
	{	s_hp(22),		s_time(30), 		"　　　　　　　岐符「天の八衢」" "\n",	SPELL_22_ame_no_yatimata,			init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)*/
	//	3.0
	{	s_hp(14),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_21_aya_misogi2,				init_00_boss_clip000,		boss_move_03_x_douki,					},/*(5)"岐符「未作成カード001」"*/
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_21_aya_misogi2,				init_00_boss_clip000,		boss_move_03_x_douki,					},/*(5)"岐符「未作成カード001」"*/
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_21_aya_misogi2,				init_00_boss_clip000,		boss_move_03_x_douki,					},/*(5)"岐符「未作成カード001」"*/
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃2" "\n"*/				SPELL_21_aya_misogi2,				init_00_boss_clip000,		boss_move_03_x_douki,					},/*(5)"岐符「未作成カード001」"*/
	//	2.5
	{	s_hp(8),		s_time(40), 		"　　　　　　摘符「穎割大好評」" "\n",	SPELL_24_aya_doll,					NULL_keitai,				boss_move_03_x_douki,					},/*(4)"岐符「未作成カード002」"*/
	{	s_hp(8),		s_time(40), 		"　　　　　風説「穎割大根被害」" "\n",	SPELL_24_aya_doll,					NULL_keitai,				boss_move_03_x_douki,					},/*(4)"岐符「未作成カード002」"*/
	{	s_hp(8),		s_time(40), 		"　　　　　　過剰「山葵大被害」" "\n",	SPELL_24_aya_doll,					NULL_keitai,				boss_move_03_x_douki,					},/*(4)"岐符「未作成カード002」"*/
	{	s_hp(8),		s_time(40), 		"　　　　　大量「麦酒十\升呑過」" "\n", SPELL_24_aya_doll,					NULL_keitai,				boss_move_03_x_douki,					},/*(4)"岐符「未作成カード002」"*/
	//	2.0
	{	s_hp(20),		s_time(100),		"　　　　　　　実況「風速３Ｍ」" "\n",	SPELL_r34_GOKAN_KINOU,				init_48_r34_gokan_kinou,	boss_move_13_aya_taifu, 				},/*(5)"岐符「未作成カード003」"*/
	{	s_hp(20),		s_time(100),		"　　　　　　実況「風速３３Ｍ」" "\n",	SPELL_r34_GOKAN_KINOU,				init_48_r34_gokan_kinou,	boss_move_13_aya_taifu, 				},/*(5)"岐符「未作成カード003」"*/
	{	s_hp(20),		s_time(100),		"　　　　　　実況「風速９８Ｍ」" "\n",	SPELL_r34_GOKAN_KINOU,				init_48_r34_gokan_kinou,	boss_move_13_aya_taifu, 				},/*(5)"岐符「未作成カード003」"*/
	{	s_hp(20),		s_time(100),		"　　　　　　実況「風速測定中」" "\n",	SPELL_r34_GOKAN_KINOU,				init_48_r34_gokan_kinou,	boss_move_13_aya_taifu, 				},/*(5)"岐符「未作成カード003」"*/
	//	1.5
	{	s_hp(20),		s_time(99), 		"　　　　　　路符「小耳の調べ」" "\n",	SPELL_1d_amefuri_test,				init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)"岐符「未作成カード004」"*/
	{	s_hp(20),		s_time(99), 		"　　　　　　路符「小手の調べ」" "\n",	SPELL_1d_amefuri_test,				init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)"岐符「未作成カード004」"*/
	{	s_hp(20),		s_time(99), 		"　　　　　　路符「胡弓の調べ」" "\n",	SPELL_1d_amefuri_test,				init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)"岐符「未作成カード004」"*/
	{	s_hp(20),		s_time(99), 		"　　　　追跡「コロンボの調べ」" "\n",	SPELL_1d_amefuri_test,				init_00_boss_clip111,		boss_move_01_taihi_ue_naka, 			},/*(4)"岐符「未作成カード004」"*/
	//	1.0
	{	s_hp(12),		s_time(99), 		"　　華符「うろおぼえ芳華絢爛」" "\n",	SPELL_25_houka_kenran,				init_00_boss_clip000,		boss_move_01_taihi_ue_naka, 			},/*(5)*/
	{	s_hp(12),		s_time(99), 		"　　　　　　　塞符「山神渡御」" "\n",	SPELL_26_aya_saifu, 				init_00_boss_clip000,		boss_move_01_taihi_ue_naka, 			},/*(5)*/
	{	s_hp(64),		s_time(99), 		"　　　　塞符「天上天下の照國」" "\n",	SPELL_26_aya_saifu, 				init_00_boss_clip000,		boss_move_01_taihi_ue_naka, 			},/*(5)*/
	{	s_hp(64),		s_time(99), 		"　　　　塞符「唯我独尊の照國」" "\n",	SPELL_26_aya_saifu, 				init_00_boss_clip000,		boss_move_01_taihi_ue_naka, 			},/*(5)*/
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	//	0.5
	//	0.0

//----------------------------------------
//	SPELL_1e_kaguya01		ボス行動、第 1形態
//	SPELL_1f_kaguya04		ボス行動、第 4形態
	// 3面ボス、easyはそこそこ簡単に。他はそれなりに。
// 輝夜 3面 								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*2.0),	s_time(500),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 28672==8192*3.5 */
	{s_hp(4*7+32*3.0),	s_time(500),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 28672==8192*3.5 */
	{s_hp(4*7+32*3.0),	s_time(500),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 28672==8192*3.5 */
	{s_hp(4*7+32*3.0),	s_time(500),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 28672==8192*3.5 */
	// 3.5
	{	s_hp(12),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1e_kaguya01,					boss_init_kaguya,			boss_move_11_kaguya_yureru, 			}, // 密着(5)還り弾、赤、青。自機狙い連弾(8)赤18セット(秒)ぐらい(始めの5秒は出さない)。(輝夜一定間隔で移動、終了後中央へ移動)
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1e_kaguya01,					boss_init_kaguya,			boss_move_11_kaguya_yureru, 			}, // 密着(5)還り弾、赤、青。自機狙い連弾(8)赤18セット(秒)ぐらい(始めの5秒は出さない)。(輝夜一定間隔で移動、終了後中央へ移動)
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1e_kaguya01,					boss_init_kaguya,			boss_move_11_kaguya_yureru, 			}, // 密着(5)還り弾、赤、青。自機狙い連弾(8)赤18セット(秒)ぐらい(始めの5秒は出さない)。(輝夜一定間隔で移動、終了後中央へ移動)
	{	s_hp(16),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1e_kaguya01,					boss_init_kaguya,			boss_move_11_kaguya_yureru, 			}, // 密着(5)還り弾、赤、青。自機狙い連弾(8)赤18セット(秒)ぐらい(始めの5秒は出さない)。(輝夜一定間隔で移動、終了後中央へ移動)
	// 3.0
	{	s_hp(12),		s_time(40), 		" 　　　　　　難題「未作成E01」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 1.龍の頸の玉	(輝夜中央固定、青赤紫緑黄の丸弾、短レーザー)4セットx
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成N01」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 1.龍の頸の玉	(輝夜中央固定、青赤紫緑黄の丸弾、短レーザー)4セットx
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成H01」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 1.龍の頸の玉	(輝夜中央固定、青赤紫緑黄の丸弾、短レーザー)4セットx
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成L01」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 1.龍の頸の玉	(輝夜中央固定、青赤紫緑黄の丸弾、短レーザー)4セットx
	// 2.5
	{	s_hp(12),		s_time(40), 		" 　　　　　　難題「未作成E02」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 2.仏の御石の鉢
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成N02」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 2.仏の御石の鉢
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成H02」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 2.仏の御石の鉢
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成L02」" "\n",	SPELL_1e_kaguya01,					init_set_dolls_kaguya_T01,	boss_move_11_kaguya_yureru, 			},// 2.仏の御石の鉢
	// 2.0
	{	s_hp(12),		s_time(40), 		" 　　　　　　難題「未作成E03」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 3.火鼠の皮衣
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成N03」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 3.火鼠の皮衣
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成H03」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 3.火鼠の皮衣
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成L03」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 3.火鼠の皮衣
	// 1.5
	{	s_hp(12),		s_time(40), 		" 　　　　　　難題「未作成E04」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 4.燕の子安貝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成N04」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 4.燕の子安貝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成H04」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 4.燕の子安貝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成L04」" "\n",	SPELL_1f_kaguya04,					init_set_dolls_kaguya_T03,	boss_move_12_kaguya_funya_idou, 		},// 4.燕の子安貝
	// 1.0
	{	s_hp(12),		s_time(40), 		" 　　　　　　難題「未作成E05」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},// 5.蓬莱の玉の枝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成N05」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},// 5.蓬莱の玉の枝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成H05」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},// 5.蓬莱の玉の枝
	{	s_hp(16),		s_time(40), 		" 　　　　　　難題「未作成L05」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},// 5.蓬莱の玉の枝
	// 0.5
	{	s_hp(64),		s_time(60), 		" 　　　難題「蓬莱の玉の枝E06」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},//
	{	s_hp(64),		s_time(60), 		" 　　　難題「蓬莱の玉の枝N06」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},//
	{	s_hp(64),		s_time(60), 		" 　　　難題「蓬莱の玉の枝H06」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},//
	{	s_hp(64),		s_time(60), 		" 　　　難題「蓬莱の玉の枝L06」" "\n",	SPELL_1c_kakuya_tamanoe,			init_set_dolls_kaguya_T02,	boss_move_01_taihi_ue_naka, 			},//
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//----------------------------------------
	// 2面ボスなので、適当に易しく。
// 魅魔 2面 								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*1.4),	s_time(400),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+10), s_time(400),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+26), s_time(400),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 20480==8192*2.5 */
	{s_hp(4*7+32*2+36), s_time(400),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 20480==8192*2.5 */
	// 2.000 (12==32*0.375) // easy(3) やたら短いのは道中で死んでパワーダウンを想定している。パワーダウンなので弾力がないが、体力が極端に少ないので次の段階に速く移行させ弾消しにつなげる。
	{	s_hp(7),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1a_mima_toge, 				NULL_keitai,				boss_move_10_mima_keitai,				},
	{	s_hp(10),		s_time(20), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1a_mima_toge, 				NULL_keitai,				boss_move_10_mima_keitai,				},
	{	s_hp(10),		s_time(30), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1a_mima_toge, 				NULL_keitai,				boss_move_10_mima_keitai,				},
	{	s_hp(10),		s_time(40), 		NULL,/* "通常攻撃" "\n"*/				SPELL_1a_mima_toge, 				NULL_keitai,				boss_move_10_mima_keitai,				},
	// 2.--
	{	s_hp(9),		s_time(20), 		" 　　　未定「未作成カードE01」" "\n",	SPELL_27_hosigata_test, 			NULL_keitai,				boss_move_10_mima_keitai,				},	/* 通常タイプ */
	{	s_hp(10),		s_time(20), 		" 　　　未定「未作成カードN01」" "\n",	SPELL_27_hosigata_test, 			NULL_keitai,				boss_move_10_mima_keitai,				},	/* 通常タイプ */
	{	s_hp(20),		s_time(40), 		" 　　　未定「未作成カードH01」" "\n",	SPELL_27_hosigata_test, 			NULL_keitai,				boss_move_10_mima_keitai,				},	/* 通常タイプ */
	{	s_hp(10),		s_time(66), 		" 　　　未定「未作成カードL01」" "\n",	SPELL_27_hosigata_test, 			NULL_keitai,				boss_move_10_mima_keitai,				},	/* 通常タイプ */
	// 1.625
	{	s_hp(14),		s_time(40), 		"　　闇符「ディマーケイション」" "\n",	SPELL_29_rumia_demarcation, 		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */	// "　　 闇符「ディマーケイション」"
	{	s_hp(24),		s_time(40), 		"　　闇符「ディマーケイション」" "\n",	SPELL_29_rumia_demarcation, 		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	{	s_hp(29),		s_time(40), 		"　　闇符「ディマーケイション」" "\n",	SPELL_29_rumia_demarcation, 		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	{	s_hp(34),		s_time(40), 		"　　闇符「ディマーケイション」" "\n",	SPELL_29_rumia_demarcation, 		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	// 1.00
	{	s_hp(26),		s_time(40), 		NULL,/* "通常攻撃" "\n"*/				SPELL_23_meirin_magaru_kunai,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	{	s_hp(24),		s_time(40), 		NULL,/* "通常攻撃" "\n"*/				SPELL_23_meirin_magaru_kunai,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	{	s_hp(28),		s_time(50), 		NULL,/* "通常攻撃" "\n"*/				SPELL_23_meirin_magaru_kunai,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	{	s_hp(44),		s_time(60), 		NULL,/* "通常攻撃" "\n"*/				SPELL_23_meirin_magaru_kunai,		NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 上広タイプ */
	// 1.--
	{	s_hp(16),		s_time(40), 		"　　　　　　　華符「芳華絢爛」" "\n",	SPELL_25_houka_kenran,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 通常タイプ */
	{	s_hp(18),		s_time(40), 		"　　　　　　　華符「芳華絢爛」" "\n",	SPELL_25_houka_kenran,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 通常タイプ */
	{	s_hp(18),		s_time(40), 		"　　　　　　　薫符「芳薫絢爛」" "\n",	SPELL_25_houka_kenran,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 通常タイプ */
	{	s_hp(22),		s_time(40), 		"　　　　　　　蘭符「芳華兼蘭」" "\n",	SPELL_25_houka_kenran,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},	/* 通常タイプ */
	// 1.--
	{	s_hp(10),		s_time(60), 		" 　　　未定「未作成カードE05」" "\n",	SPELL_18_hana_test, 				NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(12),		s_time(60), 		" 　　　未定「未作成カードN05」" "\n",	SPELL_18_hana_test, 				NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(14),		s_time(60), 		" 　　　未定「未作成カードH05」" "\n",	SPELL_18_hana_test, 				NULL_keitai,				boss_move_02_xy_hidouki,				},
	{	s_hp(14),		s_time(60), 		" 　　　未定「未作成カードL05」" "\n",	SPELL_18_hana_test, 				NULL_keitai,				boss_move_02_xy_hidouki,				},
	// 1.0
	{	s_hp(36),		s_time(60), 		" 　　　未定「てすとカードE06」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},// 未定。
	{	s_hp(36),		s_time(60), 		" 　　　未定「てすとカードN06」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},// 未定。
	{	s_hp(36),		s_time(60), 		" 　　　未定「てすとカードH06」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},// 未定。
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/	// (Lunatic は一段階少ない。ここで終了する)
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//----------------------------------------
	// 1面ボスなので、(少なくとも easy、normal あたりは)難しく出来ない。
// アリス 1面								"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
	{s_hp(4*7+32*0.75), s_time(300),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 16384==8192*2 */	/* "通常攻撃"の時間(?) */ /* "通常攻撃"のライフ */
	{s_hp(4*7+32*0.75), s_time(300),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 16384==8192*2 */	/* "通常攻撃"の時間(?) */ /* "通常攻撃"のライフ */
	{s_hp(4*7+32*1.00), s_time(300),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 16384==8192*2 */	/* "通常攻撃"の時間(?) */ /* "通常攻撃"のライフ */
	{s_hp(4*7+32*1.25), s_time(300),		NULL,/* "形態変更" "\n"*/				SPELL_00,							init_00_boss_clip000,		kaiwa_00_keitai,						},/* 16384==8192*2 */	/* "通常攻撃"の時間(?) */ /* "通常攻撃"のライフ */
	// 1.25 easy(10) 道中で[F]出るので、パワーは問題ない。まず始めに弾幕は簡単という事に慣れてもらう為、長め。(easy はプレイヤーに死んでもらっては困るので、ボスと戦った気にさせるのが難しい)
	{	s_hp(8),		s_time(12), 		NULL,/* "通常攻撃" "\n"*/				SPELL_14_alice_youmu300,			NULL_keitai,				boss_move_01_taihi_ue_naka, 			},// 明らかに簡単な弾幕
	{	s_hp(10),		s_time(16), 		NULL,/* "通常攻撃" "\n"*/				SPELL_14_alice_youmu300,			NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(9),		s_time(16), 		NULL,/* "通常攻撃" "\n"*/				SPELL_13_alice_suwako,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	{	s_hp(8),		s_time(16), 		NULL,/* "通常攻撃" "\n"*/				SPELL_13_alice_suwako,				NULL_keitai,				boss_move_01_taihi_ue_naka, 			},
	// 1.--
	{	s_hp(16),		s_time(12), 		"　　　　　懐古「紅の魔法Lv.2」" "\n",	SPELL_15_alice_aka_2nd, 			NULL_keitai,				boss_move_01_taihi_ue_naka, 			},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(18),		s_time(16), 		" 　　　　懐古「紅の魔法Lv.16」" "\n",	SPELL_15_alice_aka_2nd, 			NULL_keitai,				boss_move_01_taihi_ue_naka, 			},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(16),		s_time(18), 		"　　　　懐古「紅の魔法Lv.256」" "\n",	SPELL_15_alice_aka_2nd, 			NULL_keitai,				boss_move_04_xy_douki_differential32,	},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(14),		s_time(16), 		"　　　懐古「紅の魔法Lv.65536」" "\n",	SPELL_15_alice_aka_2nd, 			NULL_keitai,				boss_move_04_xy_douki_differential32,	},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	// 1.-- easy(4) 「パーフェクトフリーズ」は一定の事故率がある為、初心者向きでは無い。拠って不必要に短くする。
	{	s_hp(8),		s_time(20), 		" 　　 試作「カード語のてすと」" "\n",	SPELL_44_ruiz3_test,				NULL_keitai,				boss_move_02_xy_hidouki,				},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(10),		s_time(20), 		"　凍符「パーフェクトフリーズ」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(12),		s_time(30), 		"　凍符「パーティクルフリーク」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	{	s_hp(16),		s_time(20), 		"　凍符「ブリザードフローズン」" "\n",	SPELL_11_perfect_freeze,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* "蒼符「溺愛の仏蘭西人形」"のライフ */
	// 1.00
	{	s_hp(64),		s_time(40), 		"　蒼符「薄愛のマトリョーシカ」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* " 　蒼符「薄愛のマトリョーシカ」"白符「博愛の円谷人形」 */ 	//(r33p)boss_move_04_xy_douki_differential
	{	s_hp(64),		s_time(60), 		"　蒼符「溺愛のマトリョーシカ」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* " 　蒼符「溺愛のマトリョーシカ」"白符「博愛の円谷人形」 */ 	//(r33p)boss_move_04_xy_douki_differential
	{	s_hp(64),		s_time(120),		"　蒼符「自戒のマトリョーシカ」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* " 　蒼符「自戒のマトリョーシカ」"白符「博愛の円谷人形」 */ 	//(r33p)boss_move_04_xy_douki_differential
	{	s_hp(80),		s_time(77), 		"　蒼符「自害のマトリョーシカ」" "\n",	SPELL_16_alice_zako_doll,			NULL_keitai,				boss_move_02_xy_hidouki,				},/* " 　蒼符「自害のマトリョーシカ」"白符「博愛の円谷人形」 */ 	//(r33p)boss_move_04_xy_douki_differential
// r36 番兵(強制撃破。残りボスHPが幾らあっても、ボス倒す。)
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
	{	s_hp(12),		s_time(99), 		NULL,									SPELL_00,							gekiha_keitai,				NULL_keitai,							},/*[撃破]*/
//											"eeddccbbaa99887766554433221100",'\n\0' ワーク文字列バッファ長をこれだけしか用意しない予定なので、あふれたら字が出ない。 */
};
	/*
	マトリョーシカは、露西亜人形でいいのかな？人形というよりより民芸品の趣がある。
	最近は萌えマトリョーシカの需要が日本からあるらしい。
	//
	日本の気象庁は風速17m以上の風を「台風」と定義。
	国際気象機関(WMO)では風速33m以上のものを「typhoon」と定義。それ以下は「storm」。
	*/

/* " 　　　　操符「淡い眼の案山子」"白符「博愛の円谷人形」 */
/* " 　　　　　操符「幻の機巧人形」"白符「博愛の円谷人形」 */
/* " 　　　　　　操符「古の流し雛」"白符「博愛の円谷人形」 */
/* " 　操符「呪のクラッシュダミー」"白符「博愛の円谷人形」 */


//	" 　　　蒼符「博愛の仏蘭西人形」" "\n"
//	" 　蒼符「博愛のオルレアソ\人形」" "\n" " 　蒼符「博愛のオルレアン人形」"...現在の方式では無理です。
//	{	 (1024*16), 	s_time(40), 		"　操符「未作成の阿蘭陀人形L1」" "\n",	SPELL_00,							NULL_keitai,				alice_04_keitai,						},/* 白符「博愛の円谷人形」 */
//	{	(20000*4),		s_time(20), 		"操符「未作成の伊太利亜人形L2」" "\n",	SPELL_00,							NULL_keitai,				boss_move_02_xy_hidouki,				},/* 炎符「浅草の人形焼き」 */
//	{	 (5000*4),		s_time(20), 		"　操符「未作成の英吉利人形L3」" "\n",	SPELL_00,							NULL_keitai,				alice_02_keitai,						},
//	{	 (5000*4),		s_time(20), 		"　操符「未作成の露西亜人形L4」" "\n",	SPELL_00,							NULL_keitai,				alice_02_keitai,						},
//	{	 (5000*4),		s_time(80), 		"　　操符「未作成の瑞西人形L5」" "\n",	SPELL_00,							NULL_keitai,				alice_02_keitai,						},
//	{	 (5000*4),		s_time(80), 		"　操符「未作成の白耳義人形L6」" "\n",	SPELL_00,							NULL_keitai,				alice_02_keitai,						},
//	{	 (5000*4),		s_time(80), 		"　　操符「未作成の波蘭人形L7」" "\n",	SPELL_00,							NULL_keitai,				alice_02_keitai,						},

