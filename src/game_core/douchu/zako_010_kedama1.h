
/*---------------------------------------------------------
	東方模倣風 〜 Toho Imitation Style.
	http://code.google.com/p/kene-touhou-mohofu/
	-------------------------------------------------------
	道中のザコ
	-------------------------------------------------------
		"毛玉1",	"BADGUY",
	-------------------------------------------------------
	本家毛玉
---------------------------------------------------------*/

/*---------------------------------------------------------
	敵移動
---------------------------------------------------------*/

static void my_nerai(OBJ *src)
{
	REG_00_SRC_X	= (src->target_x256);						/* 弾源x256 */
	REG_01_SRC_Y	= (src->target_y256-t256(64)/*+(20)*/); 	/* 弾源y256 */
	set_REG_DEST_XY(src);
	tmp_angleCCW65536_src_nerai();
	//------------------
	HATSUDAN_01_speed256	= (t256(1.0));
//	HATSUDAN_03_angle65536	= (HATSUDAN_03_angle65536);
	sincos256();/*(破壊レジスタ多いので注意)*/
	src->vx256 = REG_03_DEST_Y;//sin_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	src->vy256 = REG_02_DEST_X;//cos_value_t256 // 下CCWの場合(右CWの場合ととxyが逆)
	//------------------
}

static void move_kedama1(OBJ *src)
{
	if (512 > src->jyumyou)/* 退場 */
	{
		my_nerai(src);
		gamen_gai_nara_zako_osimai(src);/* 画面外ならおしまい */
	}
	else
	if (512+64 > src->jyumyou)/* */
	{
		if (0==(src->jyumyou & 0x0f))
		{
			if (ENEMY_LAST_SHOT_LINE256 > src->cy256)	/* このラインより下からは敵が撃たない */
			{
				zako_shot_supeka(src, ZAKO_SPEKA_1e_kedama1);
			}
		}
	}
	else
//	if (512+64+64 > src->jyumyou)	/* 登場する */
	{
		my_nerai(src);
		{
			OBJ *zzz_player;
			zzz_player = &obj99[OBJ_HEAD_02_0x0900_KOTEI+FIX_OBJ_00_PLAYER];
			if (//(src->cx256 >= zzz_player->cx256) ||
				(src->cy256 > t256(GAME_HEIGHT/2) ) /*(480-80)*/ /*(272-32)*/
			 )
			{
				src->vy256 = (-src->vy256);
				src->jyumyou	= (512+64-1);
				/* 第二目標は、 */
				src->target_x256		= t256(((480-128)/2));	// t256(-100)
				src->target_y256		= t256(0);/*((zzz_player->cy256)&(128-1))*/
				src->speed256			= t256(2.5/*5.0*/);/*fps_factor*/	/*6*/
			}
		}
	}
	/* 移動する */
	src->cx256 += (((src->vx256)*(src->speed256))>>8);
	src->cy256 += (((src->vy256)*(src->speed256))>>8);
	/* アニメーション */
	src->zako_anime_rotate_angle1024 = ( 10);
	zako_anime_type04(src); 	/* グラ回転 */
}

/*---------------------------------------------------------
	敵を追加する
---------------------------------------------------------*/

static void regist_zako_010_kedama1(GAME_COMMAND *l, OBJ *h)
{
	h->color32				= MAKE32RGBA(0xff, 0xff, 0xff, 0xaa);		/*白っぽく */
//
	h->jyumyou			= (512+64+64);
	{
		/* 第一目標はプレイヤーのいた位置 */
		OBJ *zzz_player;
		zzz_player = &obj99[OBJ_HEAD_02_0x0900_KOTEI+FIX_OBJ_00_PLAYER];
		h->target_x256				= (zzz_player->cx256);
		h->target_y256				= (zzz_player->cy256);
	}
	h->vx256				= (0);
	h->vy256				= (0);
//	h->speed256 			= ((ra_nd()&((256*2)-1)))*(1+difficulty+teki_rank/3);/*fps_factor*/
//	h->speed256 			= ((ra_nd()&((256*2)-1))) + (((cg_game_di fficulty)<<8)+ (/*teki_rank*/5<<7/**86*2*/) );/*fps_factor*/
//	h->speed256 			= ((ra_nd()&((256*2)-1))) + (((3)<<8)+ (/*teki_rank*/5<<7/**86*2*/) );/*fps_factor*/
//	h->speed256 			= ((ra_nd()&((256*2)-1))) + ((t256(5.5) ) );/*fps_factor*/ /*(easy==2.5 normal==3.5 hard==4.5 lunatic==5.5)*/
	h->speed256 			= ((ra_nd()&((256*2)-1))) + ((t256(4)));/*fps_factor*/
}
