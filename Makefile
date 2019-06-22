
#------------------------------------------------------------------------------
#  東方模倣風 ～ Toho Imitation Style.  Makefile
#------------------------------------------------------------------------------

# (r33)動作確認済みpsp
# 1.00    (psp-1000最初期のFW)
# 3.60 M33(psp-2000最初期のCFW)
# 上記のpspで動作確認を行いました。
# これ以外は多分動くんじゃないかと思い、確認していません。

# このファイルで '。' か '.' が行末にあるのはコメントです。

#------------------------------------------------------------------------------
# revision setting. 東方模倣風のバージョンや名前を決めます。
#------------------------------------------------------------------------------

TARGET = mohoufu

#RELESE_DATE = 2011/12/04(r39)冬
#RELESE_DATE = 2011/09/04(r38)秋
RELESE_DATE = 2011/12/04

VERSION_MAJOR =39
VERSION_MINOR =1

# psp の XMB 設定
# 0 == タイトルの文字無し、XMB背景あり。リリース版(r34とか)。
# 1 == タイトルの文字あり、XMB背景無し。アップデート版(r34u1とか)。
#USE_EBOOT_TITLE = 0
USE_EBOOT_TITLE = 1

# 注意: タイトル文字を付けると背景が付けられません。

#------------------------------------------------------------------------------
# developping tools setting. 東方模倣風のコンパイル環境を決めます。
#------------------------------------------------------------------------------

# 0 == cygwin を使う。(通常開発)。
# 1 == pspsdk-setup-0.11.1.exe を使う。( Minimalist PSP homebrew SDK for Windows. version 0.11.1 )。
# 1 == pspsdk-setup-0.11.2r2.exe(2011-05-18) を使う。
#// まだ未検証 1 == pspsdk-setup-0.11.2r3.exe(2011-06-01) を使う。
USE_MINIMALIST_PSP_SDK = 1
#USE_MINIMALIST_PSP_SDK = 0


# r34から Minimalist PSP homebrew SDK for Windows.(以下minimalist) へ対応しました。
# minimalist の make.exe は制御構文の字下げに対応していないので、
# Makefile で制御構文の字下げはできません。(cygwin の make は制御構文の字下げに対応しています。)
# r33までの Makefile は字下げをしているので、r33までの Makefile を minimalist でコンパイルする場合は
# 字下げを全て修正してください。(字下げを修正しないと正常にコンパイルできません)
# r33までのコンパイルをする場合で、GCCの仕様違い等によりエラーが出る場合は、
# r33u2やr33u0のソースを基準に修正してください。(r33とr33u0を比較する)
# 模倣風の Makefile は制御構文の入れ子を多用している為、 Makefile が多少見にくいかも知れません。
# r33までは不必要でもなるべく Makefile に残しておく方針(標準SDL対応)でしたが、
# r34からは(標準SDLはアンサポートにして)なるべく不必要な機能は削除する方針に切り替えました。

# うち(231)の環境では start.bat(添付) で環境変数設定してるけど、他の環境は知らない。

#------------------------------------------------------------------------------
# PSP setting.
#------------------------------------------------------------------------------

# psp-2000対応。
PSP_LARGE_MEMORY = 1

# 3.71以降(つまりpsp-2000拡張メモリ)対応ってこと(らしい)。
PSP_FW_VERSION = 371

# 注意: 署名版は fw1.00 では起動できません。(BUILD_PRX = 1が無理)
#PSP_SYOMEI_OFW = 0
PSP_SYOMEI_OFW = 1

# 注意: (r38)Minimalistの場合、署名版は MusicRoom に入るとハングアップします。原因はメモリ不足なのですが、
# 時間内に原因を追求しきれませんでした。
# (r38)cygwinの場合、署名版は メモリ不足にならないので、問題ありません。 MusicRoom に入ってもハングアップしません。

#------------------------------------------------------------------------------
# OFW setting.
#------------------------------------------------------------------------------
# 参考 http://pspbannoukaizou.blog50.fc2.com/blog-entry-157.html
# 800200D9 メモリブロックを割り当てられませんでした。  Failure to allocate memory block.
# 800200D9 = Failure to allocate memory block (ex. missing PSP)
# 80020148 サポートされていないPRXを使用しています。
# リカバリーモードより「Advanced configration」→「Execute boot.bin in UMD/ISO」をDisabledにして下さい。
# 80020148 = Unsupported PRX type | This error also seems to appear when you are running an iso with a fake mem. stick

# prx->eboot   // 起動に失敗しました(800200D9) (PRXだけどメモリ不足? )
# eboot->eboot // 起動に失敗しました(80020148) (PRXでないので無理?)

# ENCRYPT と BUILD_PRX の 2項目 はペア。古い *.elf があるとリコンパイル失敗するので注意。
ifneq ($(PSP_SYOMEI_OFW),1)
	# 0 == 非署名版、fw1.00対応版
	APP_UTF8_SYMEI_STR = $(APP_UTF8_HI_SYOMEI_BAN)
	# prx->eboot   // FW1.00			起動に失敗しました(80020148)
	# fw1.00, prxは無理なのかな(???)
	## 暗号化しない。
	#ENCRYPT = 0
	## PRXでビルトしない。(EBOOT.PBPでビルトする)
	#BUILD_PRX = 0
	# BUILD_PRX = 1 の場合、fw1.00で起動できません。
	# src/game_core/bootmain.cで利用する。
	CORE_CFLAGS += -DAPP_SYOMEI_OFW=0
else
	APP_UTF8_SYMEI_STR = $(APP_UTF8_SYOMEI_BAN)
	# 1 == 署名版(cfw5.00m33-6 では ok だった)
	# 公式FWで起動出来るように署名を付加する。
	## 暗号化する。
	ENCRYPT = 1
	# (???)EBOOT.PBPじゃなくて、*.prxをビルトする。(ENCRYPT = 1の場合必ず必要???)
	## PRXでビルトする。(EBOOT.PBPでビルトしない)
	BUILD_PRX = 1
	# src/game_core/bootmain.cで利用する。
	CORE_CFLAGS += -DAPP_SYOMEI_OFW=1
endif
#BUILD_PRX = 1


#------------------------------------------------------------------------------
# Compile option flag. (主にデバッグ用)
#------------------------------------------------------------------------------

# 1 == GNU PROFILER を使う(game core)
#USE_PROFILE = 1
USE_PROFILE = 0

# 1 == GNU PROFILER を使う(ライブラリ)(USE_PROFILE = 1が必要)
#USE_LIB_PROFILE = 1
USE_LIB_PROFILE = 0

# 1 == FPU例外を無効にする
USE_FPU_HACK = 1
#USE_FPU_HACK = 0

#------------------------------------------------------------------------------
# Debug information. (デバッグ用、ここを変えても EBOOT.PBP は同じ)
#------------------------------------------------------------------------------
# デバッグ用。グローバル変数の配置確認などしたい場合。
#------------------------------------------------------------------------------

# 0 == デバッグ用のシンボル配置情報を出力しない。
# 「ライブラリの具体的な依存関係(実際の配置)」 や
# 「グローバル変数の配置」、
# 「データーセクションの実際の.align調整(「*fill*」ってのがGCCが.alignした奴)」
# 等が知りたくなった場合のデバッグ情報。
#DEBUG_MAP = 0
DEBUG_MAP = 1

#------------------------------------------------------------------------------
# Compile option flag.
#------------------------------------------------------------------------------
# 模倣風専用SDLライブラリ: (2011-02-16)現在のpspのSDLは色々バグがあります。(仮に描画に一切SDLしか使わなくてもSDL自体にバグがある。)
# pspの標準SDLでは、ソフトウェアーサーフェイスを明示的に指定しても、ハードウェアーサーフェイスが使われる場合があるのですが、
# pspのハードウェアーを変な風に使っている為、変な所で処理落ちします。この件は標準SDLを使う限り回避不能です。
# PSPLでは、SDLのハードウェア支援(gu)を全カットしてあります。その方が変なタイミングでGPUを使わないので実行速度が速いです。
# 模倣風では USE_PSPL = 1 以外サポートしません。
#------------------------------------------------------------------------------

# PSPL == SDLを模倣風用にカスタマイズした専用ライブラリ。
# (模倣風に必要無い機能をバッサリカットしたサブセット版。初期化処理をしない等本家SDLと動作が違う。)
# 名前とか定数とかがSDLなんちゃらなので、SDL関連は同時には一切使用できない。
# 1 == USE_PSPL (模倣風用SDL(PSPL)を使う)
# 0 == USE_PSPL (標準SDLは0,アンサポート)
USE_PSPL = 1
#USE_PSPL = 0

#------------------------------------------------------------------------------
# Custom Lib option flag. (カスタマイズ)
#------------------------------------------------------------------------------
# 注意: ここのカテゴリのオプションを変更した場合は、audio_mixer のリコンパイルが必ず必要です。
# (設定変更後、make rr↓してからmake↓推奨)
#------------------------------------------------------------------------------
# FAQ. Q:「 audio_mixer 」って何よ？
# 「 audio_mixer 」は SDL_mixer.a の改造版です。
# audio_mixerは単体で使用できません。(SDL.aが要る)理由は、
# 1. SDLの標準ファイル入出力機能を使用している。
# 2. SDLの排斥制御機能(セマフォ)を使用している。(.ITはVERCH挟んでbufferingしてるのでセマフォは実際関係ないが、oggは再生で困る。)
# です。(SDLのタイマーは使用していない)
# mp3 に対応させるためには「 madlib.a 」が別途要ります。(madlib.aに関してはpspの場合、version違いが無いみたいなので添付してません)
#------------------------------------------------------------------------------
#  「 audio_mixer 」の改造個所は主に、
# 1. mod(mikmod)のversionが古いので、最新版(でも前世紀)にしてついでに.IT形式の読み込みを高速化した。
# 2. mod関連の mixing level の設定が ogg や mp3 と比べて小さすぎるので修正。(但し、実用的な範囲では音割れしないが音割れの可能性がある)
# 3. mod関連の内内蔵 仮想ミキサー (VERCH==Virtual-Mixer)の負荷が高すぎるので速くした。(64bit -> 32bitにしてフィルターを修正)
# 4. 必要ないエフェクタ機能(デジタル リバーブ)を排除して速くした。
#    (このエフェクタ、面白いんだけどpspには負荷が高すぎた。弾幕じゃなけりゃ1ch(ステレオなのでつまり2ch)ぐらいは実用的な速度出る)
#    (やろうと思えば ending-staff roll とか 負荷が少ない処で使えなくもない。)
# 5. 効果音チャネルが 8chしかないので 16chにした。(もっと128chぐらいまでなら増やしても(現在フィルター&エフェクト無いので)負荷なんか殆んど無いと思われる)
# 6. その他逆転再生とかループ再生とか必要ない機能はバッサリカット。(して速くした。)
# 7. 他(忘れた)
#------------------------------------------------------------------------------

# 実験中
# 0 == CUS TOM_LIB
#CUS TOM_LIB = 1
#CUS TOM_LIB = 0

# MP3の設定
# 注意: MP3の使用可否を変更した場合は、audio_mixer のリコンパイルが必ず必要です。(設定変更後、make rr↓してからmake↓推奨)

## 注意: LINK_SMPEG_MP3 と LINK_MAD_MP3 を両方 1 にする事は出来ません。
# ok 	LINK_SMPEG_MP3 = 0	LINK_MAD_MP3 = 0	MP3 とか使わない。
# ok 	LINK_SMPEG_MP3 = 1	LINK_MAD_MP3 = 0	smpeg の MP3 (～r30) を使う。(不安定かつ、遅い、かつ、ぶちぶちノイズ)
# ok 	LINK_SMPEG_MP3 = 0	LINK_MAD_MP3 = 1	libmad の mp3 (r31～)を使う。(安定度は高い、遅いけど...、45fpsぐらいに低下する。)
# NG 	LINK_SMPEG_MP3 = 1	LINK_MAD_MP3 = 1	ソースレベルで対応がないので無理、NG。

## smpeg の MP3 (～r30)
# 0 == LINK_SMPEG_MP3:標準設定 [ smpeg の MP3の使用可否 ] (0:使用しない、1:使用する)
LINK_SMPEG_MP3 = 0
#LINK_SMPEG_MP3 = 1
# smpegは、まだバグ(※1)あります。
# ※1:現在判明しているバグ:
# MPEGaudio:: MPEGaudio()内で(クラス作成時に) SDL_OpenAudio() 呼ぶのは、 SDLmixerの現在仕様では色々マズイ。

## libmad の mp3 (r31～)
# 1 == LINK_MAD_MP3:標準設定 [ libmad の MP3の使用可否 ] (0:使用しない、1:使用する)
#LINK_MAD_MP3 = 0
LINK_MAD_MP3 = 1
# madlibは中身知らないけど、 SDLmixer と分離してるから、madlib内にバグなければ多分大丈夫。

# r31:色々やってみたけど、どうしても smpeg が不安定(突然死が多い)なので、 smpeg は止めて、 libmad にしました。
# (もし仮に両方にバグが無いと想定すると)たぶんバッファオーバーランなんじゃないかな？

# 1 == LINK_OGG:標準設定 [ oggの使用可否 ] (0:使用しない、1:使用する)
# 注意: oggの使用可否を変更した場合は、audio_mixer のリコンパイルが必ず必要です。
LINK_OGG = 1
#LINK_OGG = 0

# 0 == LINK_LIBTREMOR_LOW_MEM: oggを使用する場合、どちらの libtremor を使うか選択します。
# 0: libtremor_large  を使用する。
# 1: libtremor_lowmem を使用する。
# 0 == LINK_LIBTREMOR_LOW_MEM:標準設定 [ libtremor_lowmemの使用可否 ] (0:使用しない、1:使用する)
# 注意: libtremor_lowmem の選択を変更した場合は、audio_mixer のリコンパイルが必ず必要です。
LINK_LIBTREMOR_LOW_MEM = 1
#LINK_LIBTREMOR_LOW_MEM = 0


# "MOD" というのは、"Module Music"形式の事。
# この形式のデーターにはサンプリング音声と楽譜が入っていて、リアルタイム合成で音楽を鳴らす。
# "Module Music"形式には、"*.mod" "*.s3m" "*.xm" "*.it"の代表的な4形式がある。
# このうち模倣風では IT形式(Impulse Tracker形式) を使用している。

# LINK_MOD = 0 は実験してないから判らない。
LINK_MOD = 1

#------------------------------------------------------------------------------
# Configurate Rule.
#------------------------------------------------------------------------------

SRC = src
OBJ = obj

VERSION_ALL = r$(VERSION_MAJOR)u$(VERSION_MINOR)

#CORE_CFLAGS += -DAPP_NAME_STR="KENE"
CORE_CFLAGS += -DAPP_RELEASE_VERSION=$(VERSION_MAJOR)
CORE_CFLAGS += -DAPP_UPDATE_VERSION=$(VERSION_MINOR)

include ./$(SRC)/UTF8_title.mak

#PSP_EBOOT_TITLE = kene_r34_debug
#PSP_EBOOT_TITLE = kene$(RELESE_DATE)(r35)
#PSP_EBOOT_TITLE = kene$(RELESE_DATE)(r34u0)
PSP_EBOOT_TITLE = Touhou Mohofu r40 Mod

ifneq ($(USE_EBOOT_TITLE),1)
	# 0 == リリース版(タイトルの文字無し)
	PSP_EBOOT_ICON	 = ICON0.PNG
	PSP_EBOOT_ICON1  = ICON0.PMF
	PSP_EBOOT_UNKPNG = ICON1.PNG
	PSP_EBOOT_PIC1	 = PIC1.PNG
	PSP_EBOOT_SND0	 = SND0.AT3
else
	# PSP_EBOOT_UNKPNG に画像を指定すると、タイトルの文字が出ません。
	# PSP_EBOOT_PIC1 に画像を指定すると、タイトルの文字が出ません。
	# ICON1.PNG はとりあえず作るの、めんどくさい。
	# 1 == アップデート版(タイトルの文字あり)
	PSP_EBOOT_ICON	 = ICON0.PNG
#test	PSP_EBOOT_ICON1  = ICON0.PMF
	PSP_EBOOT_UNKPNG =
	PSP_EBOOT_PIC1	 =
#test	PSP_EBOOT_SND0	 = SND0.AT3
endif

# 通常開発
EXTRA_TARGETS		 = mk_dir EBOOT.PBP


ifneq ($(USE_MINIMALIST_PSP_SDK),1)
# 通常開発(cygwin)
PSPDEV = $(shell psp-config --pspdev-path)
PSPSDK = $(shell psp-config --pspsdk-path)
else
# pspsdk-setup-0.11.1
PSPDEV = C:/pspsdk/
PSPSDK = C:/pspsdk/psp/sdk/
endif

#------------------------------------------------------------------------------
# 開発環境メモ。
#------------------------------------------------------------------------------

# 本来どの環境でも対応する筈の場合
# (↓)本来 PSPSDK で想定されている書き方。
#PSPDEV = $(shell psp-config --pspdev-path)
# (↓)本来 PSPSDK で想定されている書き方。
#PSPSDK = $(shell psp-config --pspsdk-path)
# (↓)本来 PSPSDK で想定されている書き方。(但しPSPSDKの内部相対パス仕様が変わるとコンパイル通らない)
#PSPBIN = $(PSPDEV)/psp/bin
# (↓)あまり良い書き方ではないが、$(PSPSDK)があれば$(PSPDEV)が無くてもコンパイル通る。(但しPSPSDKの内部相対パス仕様が変わるとコンパイル通らない)
#PSPBIN = $(PSPSDK)/../bin

# cygwin(pspdev) の場合(C:/cygwin/pspdev/)
##PSPDEV = /pspdev
##PSPSDK = /pspdev/psp/sdk
##PSPBIN = /pspdev/psp/bin
##PSPDEV = /usr/local/pspdev
##PSPSDK = /usr/local/pspdev/psp/sdk
##PSPBIN = /usr/local/pspdev/psp/bin

# cygwin(pspsdk) の場合(C:/cygwin/pspsdk/)
##PSPDEV = /pspsdk
##PSPSDK = /pspsdk/psp/sdk
##PSPBIN = /pspsdk/psp/bin
##PSPDEV = /usr/local/pspsdk
##PSPSDK = /usr/local/pspsdk/psp/sdk
##PSPBIN = /usr/local/pspsdk/psp/bin

# minimalist(pspsdk) の場合(C:/pspsdk/)
##PSPDEV = C:/pspsdk
##PSPSDK = C:/pspsdk/psp/sdk
##PSPBIN = C:/pspsdk/psp/bin

# (↓)本来 PSPSDK で想定されている書き方。
#SDL_CONFIG = $(PSPDEV)/psp/bin/sdl-config
# (↓)あまり良い書き方ではない。(但しPSPSDKの内部相対パス仕様が変わるとコンパイル通らない。但し$(PSPBIN)を変更後仕様に合わせればコンパイル通る。)
#SDL_CONFIG = $(PSPBIN)/sdl-config
# (↓)あまり良い書き方ではないが、$(PSPSDK)があれば$(PSPDEV)が無くてもコンパイル通る。(但しPSPSDKの内部相対パス仕様が変わるとコンパイル通らない)
#SDL_CONFIG = $(PSPSDK)/../bin/sdl-config

# sdl-config ( $(shell $(SDL_CONFIG) --libs) ) は使用できない。理由は以下の２点

# １。sdl-config に、-lSDLmain がある。これを使うと、新型psp(psp-2000)では起動できない。
# その為 libSDLmain.a の main(); 以外に main(); があり(当然psp-2000で起動させるために)
# こちらを使う(C言語はmain();関数が１つのみ、リンカは後着優先)が、
# 周辺関数の名前が同じならバッティングする危険がある。

# ２。ライブラリ間の依存関係が解消できない。
# sdl-config は SDL 以外のライブラリと依存関係が発生する場合を考慮しない為。

#------------------------------------------------------------------------------
# Library.
#------------------------------------------------------------------------------

# 参考 http://himitsu.jpn.ph/yomimono/linux/staticlink.html
# 参考 http://www.hakodate-ct.ac.jp/~tokai/tokai/gtkmm/etc/p1.htm

LIBDIR =
LDFLAGS =


#------------------- for debug.

ifneq ($(DEBUG_MAP),1)
# 通常
else
# マッピング出力(デバッグ用)
LDFLAGS += -Wl,-Map=$(TARGET)_map.txt
endif

#------------------- for debug.

ifneq ($(USE_PROFILE),1)
else
#ifneq ($(USE_LIB_PROFILE),1)
#else
# -lpspprof は SDL とリンクする場合、位置依存がある。
LIBS += -lpspprof
#endif
#	CORE_LIBS += -lpspprof
endif

# 位置が悪い場合
#＜略＞
#er.o obj/game_core/hiscore.o obj/game_core/fps.o obj/game_core/soundmanager.o obj/game_core/bg.o -lS
#DL_noGL -lSDL_mixer -lvorbisidec -lSDL_image -lpng -lz -ljpeg -lm -L/usr/local/p
#spdev/psp/lib -lSDLmain -lSDL -lm -L/usr/local/pspdev/psp/sdk/lib -lpspdebug -lp
#spgu -lpspctrl -lpspge -lpspdisplay -lpsphprm -lpspsdk -lpsprtc -lpspaudio -lc -
#lpspuser -lpsputility -lpspkernel -lpspnet_inet -lpsppower -lpspprof -lpspdebug
#-lpspdisplay -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apct
#l -lpspnet_resolver -lpsputility -lpspuser -lpspkernel -o kene.elf
#psp-fixup-imports kene.elf
#Error, could not fixup imports, stubs out of order.
#Ensure the SDK libraries are linked in last to correct this error
#make: *** [kene.elf] Error 1
# のようになりリンク出来ない。(PSPSDKのライブラリは最後にしてくれって言ってるから-lpspprofを最後にしてるのに...)
#＜略＞
#er.o obj/game_core/hiscore.o obj/game_core/fps.o obj/game_core/soundmanager.o obj/game_core/bg.o -lp
#spprof -lSDL_noGL -lSDL_mixer -lvorbisidec -lSDL_image -lpng -lz -ljpeg -lm -L/u
#sr/local/pspdev/psp/lib -lSDLmain -lSDL -lm -L/usr/local/pspdev/psp/sdk/lib -lps
#pdebug -lpspgu -lpspctrl -lpspge -lpspdisplay -lpsphprm -lpspsdk -lpsprtc -lpspa
#udio -lc -lpspuser -lpsputility -lpspkernel -lpspnet_inet -lpsppower -lpspdebug
#-lpspdisplay -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apct
#l -lpspnet_resolver -lpsputility -lpspuser -lpspkernel -o kene.elf
#make: *** [kene.elf] Interrupt
# こういう風ならリンク出来る。(-lpspprofの位置のみ違う)

# -lpspprof (例えば C:/cygwin/pspdev/psp/sdk/lib/libpspprof.a) に限らず、
#「stubs out of order.」が出る場合は、
# SDL とリンクする場合、位置依存のためリンク出来ない。
# Makefileのライブラリの位置を見直せば必ずリンクできるが、
#「$(shell $(SDL_CONFIG) --libs)」のせいで解消できない場合は結構泥沼。


#LIBS_org += -lstdc++		C++は使わない。
#LIBS_org += -lSDL_mixer	使う。
#LIBS_org += -lvorbisidec	使う。
#LIBS_org += -lSDL_image	使う。
#LIBS_org += -lpng			使う。
#LIBS_org += -lz			使う。
#LIBS_org += -ljpeg 		使う。
#LIBS_org += -lSDL_gfx
#LIBS_org += -lm			使う。
#LIBS_org += $(shell $(SDL_CONFIG) --libs)
#LIBS_org += -lpsppower 	使う。


#------------------- ogg codec.
ifneq ($(LINK_OGG),1)
##not include	## oggを使わない場合。
else
##
ifneq ($(LINK_LIBTREMOR_LOW_MEM),1)
##only large
LIBTREMOR_DIR = libtremor_large
else
##only LINK_LIBTREMOR_LOW_MEM
LIBTREMOR_DIR = libtremor_lowmem
endif
##
#ifneq ($(CUS TOM_LIB),1)
#	# CUS TOM_LIB 以外の場合
#	LIBS += -lvorbisidec
#else
#LIBS += $(OBJ)/libtremor/lib_mohou_vorbisidec.a
LIBS += $(OBJ)/$(LIBTREMOR_DIR)/lib_mohou_vorbisidec.a
#endif
endif

#------------------- 位置依存リンク。

#ifneq ($(CUS TOM_LIB),1)
#	# CUS TOM_LIB 以外の場合
#	LIBS += -lSDL_image 	アンサポート
#	LIBS += -lpng			アンサポート
#	LIBS += -ljpeg			アンサポート
#	#標準
#	#LIBS += -lpspmath		アンサポート
#else
#カスタム
#LIBS += $(OBJ)/libpspmath/libpspmath.a
#endif
LIBS += $(OBJ)/vfpu/lib_mohou_vfpu.a

LIBS += -lz

#LIBS += -lm


#-------------------
# libc 関連。
#-------------------

# (gnu標準の) libc を使わないで、(PSPSDKが用意したpsp用の) libpsplibc を使う。
#USE_PSPSDK_LIBC = 1
#とりあえずコンパイルできない環境がありそうな気がするので止めとく。(-lcと同時にリンクしてる為)

# うーん正直言ってnewlibとlibpsplibc両方リンクしてるのは良くないのですがSDLの都合で。(主に signal(); )
# (r32)とりあえずnewlibのみで。(libpsplibc使わない)
LIBS += -lc

# smpeg は C++ ですが、libstdc++.a は使いません。
#LIBS += -lstdc++

#---------------------------

### SDL関連は先(位置依存がある。)

#---------------------------

#LIBS += $(shell $(SDL_CONFIG) --libs)
# -lSDLmain があると色々おかしな事になる。 -lSDLmain はリンクしない。

#---------------------------

### PSPSDK関連は後(位置依存がある。)

LIBS += -lpsppower
#LIBS += -lpspgum
#LIBS += -lpspgu
LIBS += -lpsphprm
LIBS += -lpspaudio
LIBS += -lpsprtc

#---------------------------

#LIBS += -lpspdebug
#LIBS += -lpspdisplay
#LIBS += -lpspge
#LIBS += -lpspctrl
#LIBS += -lpspsdk
#LIBS += -lc
#LIBS += -lpspnet
#LIBS += -lpspnet_inet
#LIBS += -lpspnet_apctl
#LIBS += -lpspnet_resolver
#LIBS += -lpsputility
#LIBS += -lpspuser
#LIBS += -lpspkernel

#---------------------------
#bgu_tiny.a obj/libtremor_lowmem/lib_mohou_vorbisidec.a obj/vfpu/lib_mohou_vfpu.a
# -lz -lc -lpsppower -lpsphprm -lpspaudio -lpsprtc -lmad
# -lpspdebug -lpspdisplay
# -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apctl
# -lpspnet_resolver -lpsputility -lpspuser -lpspkernel -o kene.elf


#------------------------------------------------------------------------------
# Object Directory.
#------------------------------------------------------------------------------

OBJDIRS += $(OBJ)
OBJDIRS += $(OBJ)/font

# add after the others, in custom.mak

#------------------------------------------------------------------------------
# Object.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Include makefiles.
#------------------------------------------------------------------------------
# 模倣風のバージョン違いによる差異はこちらで吸収する。
#------------------------------------------------------------------------------

# Makefile 本体。(模倣風本体及び専用ライブラリ)
include $(SRC)/src.mak


#------------------------------------------------------------------------------
# CFLAGS.
#------------------------------------------------------------------------------

##	CFLAGS += -O2
	# 模倣風では、ここで指定しない。(このオプションは最適化の設定)

CFLAGS_OPTIMIZE += -O3
#???	署名てすと
# 参考 2011-02-07 記事更新 http://nekoyama2gillien.blog36.fc2.com/blog-entry-417.html
# CFLAGS_OPTIMIZE += -O2 -march=allegrex -mips2 -mabi=eabi -mgp32 -mlong32
# うーん良くわかんないな～。


#------------------------------------------------------------------------------
# 参考 http://www.sra.co.jp/wingnut/gcc/gcc-j.html
# GNU CC(GCC) のバージョン 2.95 に対応している。(日本語版ドラフト-17 July 2001)
# MIPS 系コンピュータ用オプション
# 以下の -m オプションが、定義されている。

# ============================================= cpuの指定
# -mcpu=<cpu type>  // psp用GCC-4.3.5時点ではこのオプションは存在しない。
# 解説: cpuを指定する。 最近のGCC(4.x.x系)では -mcpu は廃止されて、-march になった。
# 解説: psp用GCC-4.3.5時点では -mcpu はサポートされない。
# -mcpu=<cpu type>
# 命令スケジューリングの際の機種のデフォルトを <cpu type> と想定する。
# <cpu type> は、r2000、r3000、r3900、r4000、r4100、r4300、r4400、r4600、r4650、r5000、r6000、r8000、orion のどれかである。
# さらに、r2000、r3000、r4000、r5000、r6000 は、r2k(あるいは r2K)、r3k 等のように省略できる。

#------------
# http://www7.atwiki.jp/pspprogram/pages/12.html
# CPU(Allegrex)
# MIPS 32bitコア R4000
# 周波数：1～333MHz
# 浮動小数点計算能力：2.6Gflops(333MHz駆動時)
# VFPU有り
# 便利な定数がハードコード済み

# PSPに採用されているCPUは、MIPS社のR4000の32bitカスタムCPU「Allegrex」。
# 対応クロックは1～333MHz。パワーセービングのための拡張命令を持ち、FPUとVFPUが直結されている。
CPUTYPE = allegrex
#CFLAGS_OPTIMIZE += -march=allegrex
CFLAGS_OPTIMIZE += -march=$(CPUTYPE)
# http://nekoyama2gillien.blog36.fc2.com/blog-date-200911.html
# -march=<cpu type>
#	命令スケジューリングの際の機種のデフォルトを <cpu type> と想定する。
#	<cpu type> は、
#	mips1, mips2, mips3, mips4, mips5,
#	mips32, mips32r2, mips64, mips64r2,
#	r2000, r3000, r3900, r4000, r4010, r4400, r4600, r4650,
#	r6000, r8000, r10000, r12000, orion, allegrex,
#	vr4100, vr4111, vr4120, vr4130, vr4181, vr4300, vr5000, vr5400, vr5500,
#	rm5200, rm5230, rm5231, rm5261, rm5721, rm7000, rm9000,
#	4kc, 4km, 4kp, 5kc, 20kc, sb1, from-abi
#	のどれかである。
# 解説: アーキテクチャー(cpuの設計)を指定する。
# 解説: pspでは -march=allegrex らしい。

#------------

# ある特定の <cpu type> を選ぶとその特定のチップに適したスケジューリングを行なう一方で、
# -mipsX や -mabi を指定しない限り、MIPS ISA(Instruction Set Architecture、命令セットアーキテクチャ)の
# レベル 1 に合わないコードは何も生成しない。

# ============================================= MIPSタイプの指定
# ------ MIPS I/II/III/IV
# -mips1  // (pspでは指定できない。)# error: -mips1 conflicts with the other architecture options, which specify a MIPS2 processor
# -mips2  // (pspでは指定できる。  )# allegrex アーキテクチャーは MIPS II ベースなのかな？。(MIPS II準拠のr4000系を改造した物?)
# -mips3  // (pspでは指定できない。)# error: -mips3 conflicts with the other architecture options, which specify a MIPS2 processor
# -mips4  // (pspでは指定できない。)# error: -mips4 conflicts with the other architecture options, which specify a MIPS2 processor
#-mips1
#	MIPS ISA のレベル 1 の命令を発行する。これがデフォルトである。
#	r3000 が、この ISA レベルのデフォルトの CPU タイプである。
#-mips2
#	MIPS ISA のレベル 2 の命令(branch likely, square root 命令)を発行する。
#	r6000 が、この ISA レベルのデフォルトの CPU タイプである。
#-mips3
#	MIPS ISA のレベル 3 の命令(64ビット命令)を発行する。
#	r4000 が、この ISA レベルのデフォルトの CPU タイプである。
#-mips4
#	MIPS ISA のレベル 4 の命令(条件付き move 命令、プリフェッチ命令、強化された FPU 命令)を発行する。
#	r8000 は、この ISA レベルのデフォルトの cpu type である。
# CFLAGS_OPTIMIZE += -mips2
# 解説: pspでは -mips2 しか指定できないにもかかわらず、デフォルトという訳ではなく、
#	指定した場合と省略した場合の扱いが特殊なので注意。
#	pspの allegrex は MIPS II ベースだが、一部 MIPS III の命令も持つ。
#	だから -mips2 を指定してそれらがGCCでどういう扱いになるのかちょっと判らない。

#------------ CPU内のFPUレジスタのビット数設定。(VFPUはまるで関係無いので注意)
# 解説: PCのコプロセッサ(浮動小数点形式)で紅魔境で使っているものは 32bit, 64bit, 96bit(80bitかも), 128bit。
# 32bit はいわゆる(float)。
# 64bit はいわゆる(double)。
# 96bit(80bit?) は(tri double と呼ばれる形式らしい)。
# 128bit はいわゆる(long double)。
# 紅魔境のゲームエンジン側では、おそらく32bit, 64bitしか使ってないと思われるが、
# Direct X と VisualC++のランタイム をスタティックリンクしているので、こちらで  96bit(80bitかも), 128bitを使用している。
# Direct X (スタティックリンクされている)で SSE や MMX も使用している。

# 解説: -mfp32 は、PCでいう(float)を使う。
# 解説: -mfp64 は、PCでいう(double)を使う。しかしpspでは設定できない。pspで double と書けば float精度。
#-mfp32
#	32個の32ビット浮動小数点レジスタが利用可能であることを仮定する。これはデフォルトである。
#-mfp64  // (pspでは指定できない。) // error: unsupported combination: -mfp64 -msingle-float
#	32個の64ビット浮動小数点レジスタが利用可能であることを仮定する。これは、-mips3 オプションが指定されたときのデフォルトである。
CFLAGS_OPTIMIZE += -mfp32

#------------ CPU内の汎用レジスタ設定。# 1レジスタあたりのビット数
#-mgp32
#	32個の32ビット汎用レジスタが利用可能であることを仮定する。これはデフォルトである。
#-mgp64  // (pspでは指定できない。) error: '-mgp64' used with a 32-bit processor.
#	32個の64ビット汎用レジスタが利用可能であることを仮定する。これは、-mips3 オプションが指定されたときのデフォルトである。
CFLAGS_OPTIMIZE += -mgp32

#------------ long型の大きさを指定する。
#-mlong32
#	long 型、int 型、ポインタ型を強制的に 32 ビット幅にする。
#	-mlong32、-mlong64、-mint64 のどれも指定されていないと、int、long、ポインタのサイズは、ABI と選択された ISA に依存する。
#	-mabi=64 の場合、int は 32 ビット幅で long は 64 ビット幅である。
#	-mabi=eabi の場合、-mips1 か -mips2 が指定されていると、int と long は 32 ビット幅になる。
#	-mabi=eabi の場合、それより高い ISA が指定されていると、int は 32 ビット幅で、long が 64 ビット幅になる。
#	ポインタ型の幅は、long の幅と汎用レジスタの幅の小さいほうになる(これは、ISA に依存する)。
#-mlong64
#	long 型を強制的に 64 ビットにする。デフォルトについての説明とポインタの大きさについては -mlong32 を参照のこと。
#-mint64
#	long 型と int 型を強制的に 64 ビット幅にする。デフォルトについての説明とポインタの大きさについては -mlong32 を参照のこと。
# 解説: pspでは -mlong32 だとlong に 64bitを必要とするアプリがコンパイルできない。Timidityとかは -mlong64 でないとコンパイルできないと思う。
# 解説: long long はこの辺のオプションに影響されずpspでは恐らく 64 ビットになって関係ないと思われるけど、解らない。
CFLAGS_OPTIMIZE += -mlong32

#-mabi=32
#-mabi=o64  // (pspでは指定できない。たぶん)
#-mabi=n32  // (pspでは指定できない。たぶん)
#-mabi=64
#-mabi=eabi
#	指定された ABI 用のコードを生成する。
#	デフォルトの命令レベルは、32 に対しては -mips1 であり、
#	n32 に対しては-mips3、その他に対しては -mips4 である。
#	逆に、-mips1 か -mips2 を指定するとデフォルトの ABI は 32 になり、それ以外は 64 になる。
CFLAGS_OPTIMIZE += -mabi=eabi

#-mmips-as
#	MIPS アセンブラ用のコードを生成し、通常のデバッグ情報を追加するためにmips-tfile を起動する。
#	これは、OSF/rose オブジェクト形式を使っている、OSF/1 参照プラットフォーム以外の全てのプラットフォームでのデフォルトである。
#	-gstabs か -gstabs+ のどちらかのオプションを使うと、mips-tfile プログラムが、MIPS ECOFF 内に stabs 形式のデバッグ情報を包み込む。
#-mgas
#	GNU アセンブラ用のコードを生成する。これは、OSF/rose オブジェクト形式を使っている、OSF/1 の参照プラットフォームではデフォルトである。
#	また、configure のオプション --with-gnu-as が指定されたときのデフォルトでもある。

#-msplit-addresses
#-mno-split-addresses
#	アドレス定数の上位部と下位部を別々にロードするコードを生成する。
#	これにより、gcc が、アドレスの上位ビットを無駄にロードしないように最適化することが可能になる。
#	この最適化には、GNU as と GNU ld が必要になる。この最適化は、GNU as と GNU ld が標準のツールである幾つかの組み込みターゲットでは
#	デフォルトで有効になる。
#-mrnames
#-mno-rnames
#	-mrnames を指定すると、レジスタ名として、ハードウェア名の代わりに、MIPS のソフトウェア名(例えば、$4 の代わりに a0)を使ったコードを出力する。
#	このオプションをサポートしているアセンブラはAlgorithmics のアセンブラだけである。
#-mgpopt
#-mno-gpopt
#	-mgpopt オプションを指定すると、全てのデータ宣言を、テキストセクションの命令部分の前に書き出す。
#	これにより MIPS のアセンブラが小さいグローバルおよび静的データ項目に対し、二語ではなく、一語によるメモリ参照を生成することが可能になる。
#	最適化が指定されている場合には、これはデフォルトで有効になる。
#-mstats
#-mno-stats
#	-mstats オプションを指定すると、非インライン関数が処理される度に、標準エラー出力に一行出力し、
#	プログラムの統計情報(セーブされたレジスタ数、スタックの大きさ等)を表示する。
#-mmemcpy
#-mno-memcpy
#	-mmemcpy オプションを指定すると、全てのブロック移動に対し、インラインコードを生成する代わりに、
#	適切な文字列関数(memcpy かbcopy)を呼び出すようにする。
#-mmips-tfile
#-mno-mips-tfile
#	-mno-mips-tfile を指定すると、MIPS のアセンブラがデバッグ情報を追加した後のオブジェクトファイルに対し、
#	mips-tfile プログラムによる後処理を行なわない。
#	mips-tfile を実行しておかないと、デバッガからローカル変数の情報が扱えなくなる。
#	さらに、stage2 と stage3 のオブジェクトには、アセンブラに渡された一時ファイル名が、オブジェクトファイル内に埋め込まれた形で入っている。
#	このため、stage2 のオブジェクトと stage3 のオブジェクトが同じになることはない。
#	-mno-mips-tfile オプションを指定するのは、mips-tfile プログラムにバグがあり、コンパイルが行えない場合にだけに術器である。

#-msoft-float
#	浮動小数点用ライブラリ呼び出しを含む出力を生成する。
#	警告: 必要となるライブラリは GCC の一部ではない。
#	普通はその機種の通常の C コンパイラの機能が使われるが、クロスコンパイルの場合はこれをそのまま行なうことはできない。
#	クロスコンパイルの場合は、適切なライブラリ関数を自分で用意しなければならない。
#-mhard-float
#	浮動小数点命令を含む出力を生成する。これは、GCC のソースを変更しなければ、デフォルトである。

#-mabicalls
#-mno-abicalls
#	位置独立コード用に、System V.4 用の移植で使っている疑似命令.abicalls、.cpload、.cprestore を生成する(あるいは生成しない)。

#-mlong-calls
#-mno-long-calls
#	全ての呼出しを JALR 命令で行う。このためには、呼出しの前に、関数のアドレスをレジスタにロードしておく必要がある。
#	このオプションを使う必要があるのは、現在の 512 メガバイトのセグメントの外側の関数を、ポインタ経由でなく呼び出す場合である。

#-mhalf-pic
#-mno-half-pic
#	外部参照へのポインタを、テキストセクションに置くのではなく、データセクションに置いてロードするようにする。

#-membedded-pic
#-mno-embedded-pic
#	いくつかの組み込みシステム向けに適した PIC コードを生成する。全ての呼出しは PC 相対アドレスを使って行われ、
#	全てのデータのアドレスは$gp レジスタを使って扱われる。
#	これには、そのための作業のほとんどを行う GNU as と GNU ld が必要である。
#	これは、現在、ECOFF を使っているターゲットでしか動作していない。ELF では動いていない。

#-membedded-data
#-mno-embedded-data
#	可能であれば、変数を、まず最初に読み出し専用データセクションに割り当てる。
#	次に可能であれば、小データセクションに割り当てる。さもなければ、データセクションに置く。
#	こうすると、デフォルトよりも幾分遅いコードになるが、実行時に必要な RAM の量が小さくなるので、
#	いくつかの組み込みシステムにとっては望ましいだろう。

#-msingle-float
#-mdouble-float
#	-msingle-float オプションを指定すると、r4650 チップのように、浮動小数点コプロセッサが単精度演算しかサポートしていないと想定する。
#	-mdouble-float オプションを指定すると、倍精度演算を使うようになる。こちらがデフォルトである。

#-mmad
#-mno-mad
#	r4650 チップの場合のように、mad、madu、mul 命令を使うことを許す。

#-m4650
#	-msingle-float、-mmad、それに少なくとも現在のところでは、-mcpu=r4650 を有効にする。

#-mips16
#-mno-mips16
#	16ビット命令を有効にする。

#-mentry
#	疑似命令 entry と exit を使う。このオプションは -mips16 を一緒にしか使えない。

# ------- endian (pspは -EL Little Endian.)
#-EL
#	リトルエンディアン・モードのプロセッサ用にコードをコンパイルする。必要となるライブラリが存在すると仮定する。
#-EB   // (pspでは指定できない。)
#	ビッグエンディアン・モードのプロセッサ用にコードをコンパイルする。必要となるライブラリが存在すると仮定する。
# 解説: pspのcpuはリトルエンディアンなので -EL (Little Endian)。デフォルトなのであえて指定する意味が無い。

#-G<number>
#	<number> バイト以下の大きさのグローバルなデータ項目と静的なデータ項目を、
#	普通のデータセクションや bss セクションではなく、小データセクションや小 bss セクションに置く。
#	これにより、アセンブラが、通常の 2 命令のメモリ参照の代わりに、
#	グローバルポインタ(gp あるいは $28)に基づいた一命令のメモリ参照を生成することが可能になる。
#	<number> のデフォルト値は、MIPS のアセンブラを使う場合には 8 で、GNU アセンブラを使う場合には 0 である。
#	-G<number> オプションはアセンブラとリンカにも渡される。
#	全てのモジュールは、同じ値の -G<number> でコンパイルしなければならない。
# 解説: pspでは GNUアセンブラを使うので初期値が -G0 と思われる。
#CFLAGS += -G8

# ------- アセンブラにプリプロセッサを使わない
#-nocpp
#	MIPS アセンブラに対し、ユーザのアセンブラソースファイル(サフィックスが.s のもの)をアセンブルする場合に、
#	アセンブラのプリプロセッサを実行しないように指示する。
#	これらのオプションは、マシン記述の TARGET_SWITCHES マクロで定義されている。
#	これらのオプションのデフォルトも、このマクロで定義されているので、デフォルトを変更するが可能である。

# =============================================

#------------------------------------------------------------------------------


#//??? 最適化オプションとして -O2 を使う場合は、-Olimit 3000 も使う必要がある。
#//??? この二つのオプションはどちらも、configure が構築するMakefile には自動的に追加される。
#//??? make の変数 CC を上書きして MIPS のコンパイラを使うには、-Wf,-XNg1500 -Olimit 3000 を追加する必要がある。


#------------------------------------------------------------------------------
# コード品質
#

## pspはアライメントおかしいと動かないから、念の為設定。
# 関数は 32[byte]境界にアライメント。
CFLAGS += -falign-functions=32
# ループの頭は必ずアライメント。
CFLAGS += -falign-loops
# ラベル指定も必ずアライメント。
CFLAGS += -falign-labels
# ジャンプ先も必ずアライメント。
CFLAGS += -falign-jumps

#------------------------------------------------------------------------------



CFLAGS += -Wall
	# Warning があればすべて出力。
	# 模倣風では -Werror なので Warning扱いは、エラー扱いにして即コンパイル中止。

CFLAGS += -G0
	# -G0 を指定すると、(gp==$28)レジスタを使った間接アドレッシング命令を使わない(たぶん)
	# 参考 http://wfasim.dyndns.org/wordpress/?p=182
# -G<数字> は GPレジスタに関するオプション。<数字>は具体的にはバイト数。
# データセクション(あるいはbss セクション)と GPレジスタ(==$28) を使った、メモリ参照が可能になる。
# 解説: GCCでは、 -G<number> はすぺてのライブラリ/オブジェクトで統一しないと正常動作しないという仕様らしい。
#	にもかかわらず、 -G<number> が異なるライブラリ/オブジェクトはリンク可能で、
#	それが -G<number> が幾つの設定でコンパイルされたのか検出の手段が無い。
#	pspの場合、万が一ライブラリに -G0 以外でコンパイルされたライブラリ/オブジェクトが混入されていると、
#	そのライブラリ/オブジェクトの部分は正常に動作しない。
#	通常は安全側の為 -G0に指定しておいた方が良い。
#	但し、一切の外部ライブラリ/オブジェクトを使用しないならば(当然PSPSDKも使うなら自前コンパイル) -G8 とかは可能。

# -G は GPレジスタに関するオプションで -g はデバッグに関するオプション。大文字と小文字で全然意味が違う。
#???	CFLAGS += -g
#	CFLAGS += -g
#	-g はデバッグに関するオプション。って事は判るけど詳細は良く判んない。(-pg付けたら-g付けたと解釈されるのかな？)
#	C++(smpeg)使う場合は -g が要るかも知れない。っていうか要ると思う。
#	-g 付けるとほんの少し※コードが大きくなる。(※少し: r33の場合で 36[bytes])
#	r33現在 模倣風はC++無いので -gは要らない。(-lstdc++も要らない)

CFLAGS += -std=gnu99
	# 1999年の GNU 規格に沿った C言語コード とする。(暗黙の省略とか、voidポインタの扱いとか...)

#でばっぐCFLAGS += -Werror
	# Warning が発生した場合、エラー扱いにしてコンパイル中止。


##	CFLAGS += -fomit-frame-pointer
	# 模倣風では、ここで指定しない。 フレームポインタはプロファイラが使えなくなるので、後で設定。


# C/C++言語で式の型に対する最適化の設定 h ttp://www.radiumsoftware.com/0304.html
#	CFLAGS += -fstrict-aliasing
	# このオプションを「指定した場合に」速度向上のためにメモリアクセスの最適化をする。(キャストに注意しないと動かない可能性あり、速い)
	# -O2 $(CFLAGS_OPTIMIZE) では自動的に適用される。
#	CFLAGS += -fno-strict-aliasing
	# このオプションを「指定しない場合に」速度向上のためにメモリアクセスの最適化をする。(安全側、遅い)
# 何も指定しない場合は -O2 $(CFLAGS_OPTIMIZE) なら「-fstrict-aliasing」(キャストに注意しないと動かない可能性あり、速い)
##### 以下GCCの説明文
	# コンパイルされている言語に適用可能な別名規則（aliasing rule）のうち
	# 最も厳密なものをコンパイラが前提することを許します。
	# これによって、 C（およびC++）では式の型に基く最適化を動作させることになります。
	# 例えば、ある型のオブジェクトが別の型のオブジェクトと同一アドレスに位置することは、
	# それら2つの型がほとんど同一でない限り、ないものと仮定されます。
	# 例えば、 unsigned intがintの別名となることはあっても、 void*やdoubleの別名となることはありえません。
	# また、文字型は他の任意の型の別名になりえます。 以下のようなコードに特に注意してください.
	# 最後に書き込みが行われた共用体メンバとは異なるメンバから
	# 読み込みを行う習慣（「type-punning」と呼ばれる） は一般的に見られます。
	# `-fstrict-aliasing'を指定した場合でも、メモリが共用体型を通してアクセスされる場合にはtype-punningは許されます。



# 全部調べた訳じゃないけど、どういう場合に Warning扱い にするかの設定。(たぶん)
	# 模倣風では -Werror なので Warning扱いは、エラー扱いにして即コンパイル中止。


# 符号比較はデバッグ中なのでとりあえずoff。(本当は良くない)。
# off(符号比較で警告しない):符号比較の扱い
#CFLAGS += -Wno-sign-compare
# on(符号比較で警告する):符号比較の扱い。
CFLAGS += -Wsign-compare



CFLAGS += -Wunused
CFLAGS += -Wpointer-arith
CFLAGS += -Wundef
CFLAGS += -Wformat
CFLAGS += -Wwrite-strings
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wbad-function-cast

#CFLAGS += -Wmissing-prototypes # プロトタイプ宣言が無い場合に警告(→エラー)。

CFLAGS += -ffast-math
	# このオプションを指定すると、実行速度を最適化するという観点から、
	# ある面で ANSI や IEEE の規則や仕様を破ることを GCC に許す。
	# 例えば、このオプションを指定すると、GCC は、sqrt 関数の引数が負にならないとか、
	# 浮動小数点値がNaN になることはないという仮定を行なう。




#	CFLAGS += -pipe
#	CFLAGS += -freorder-blocks
#	CFLAGS += -fprefetch-loop-arrays

#------------------------------------------------------------------------------
# ループ展開に関する最適化オプション
#------------------------------------------------------------------------------
# これらのオプションを付けると pspでは遅くなる。
#------------------------------------------------------------------------------

# ========
# -fstrength-reduce
# ループの強度削減と繰り返し変数の削除の最適化を実行します。
# ループの外に出せる計算は外に出して、ステップ数を減らします。
# ========
# -frerun-cse-after-loop
# ループ最適化の実行後に共通部分式の削除をもう一度実行します。
# -fstrength-reduce で行ったことを徹底して行います。
# ========
# -frerun-loop-opt
# ループ最適化を徹底して行います。-fstrength-reduceで行ったことです。
# ループ内で変化しない式やアドレス計算がチェックされます。
# そして、そうした計算はループの外に移され、その評価値がレジスタに格納されます。
# ========
# -funroll-loops
# ループ展開最適化を実行します。
# これは、コンパイル時か実行時に繰り返し回数が決められるループにしか行われません。
# -funroll-loopsは、前述の -fstrength-reduce と -frerun-cse-after-loop を含みます。
# ========
# -funroll-all-loops
# ループ展開最適化を実行します。これは、すべてのループに対して行われ、
# 普通はプログラムの実行を遅くしてしまいます。
# (pspではループ展開はすればするほど遅くなる。)	CFLAGS += -funroll-all-loops
# ========


#------------------------------------------------------------------------------
# cygwinも Minimalist は無くてもコンパイル出来る(?)。
#CFLAGS += -I/usr/local/pspdev/psp/include
# (謎)
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#Minimalist は あると何故かコンパイル出来ない(????)。
#INCDIR += $(PSPDEV)/psp/include
# (謎)
#------------------------------------------------------------------------------

#INCDIR += $(PSPSDK)/../include

ifneq ($(USE_PSPL),1)
	# USE_PSPL 以外の場合
	#OPTION_CFLAGS += -I/pspdev/psp/include/SDL
	INCDIR += $(PSPDEV)/psp/include/SDL
	#INCDIR += $(PSPSDK)/../include/SDL
endif


# http://www.sra.co.jp/wingnut/gcc/gcc-j.html
# -fomit-frame-pointer フレームポインタを必要としない関数については、フレームポインタをレジスタに保持しないようにする。
# これにより、フレームポインタをセーブ、設定、リストアする命令をなくすことができる。
# また、多くの関数で利用可能なレジスタが一つ増える。
# また、機種によってはデバッグが不可能になる。 (pspでは -pg が使えなくなる)。

# (現在r36異常動作の為off。pspでは遅くなる?) CFLAGS += -ftracer
# (現在r36異常動作の為off。pspでは遅くなる?) CFLAGS += -fstrength-reduce

# どちらのオプションが悪いのか実験していないが、r36では、
# これらを付けると、キャラ選択画面がちらついたり、色々おかしい。
# これらのオプションはループ展開等するらしく、
# サイズが増えるとキャッシュに収まりきらなくなり psp では速度低下する。

ifneq ($(USE_PROFILE),1)
#	CORE_CFLAGS += -ftracer
#	CORE_CFLAGS += -fstrength-reduce
	CORE_CFLAGS += -fomit-frame-pointer
else
	CORE_CFLAGS += -DENABLE_PROFILE
	CORE_CFLAGS += -pg
endif

ifneq ($(USE_LIB_PROFILE),1)
#	LIB_CFLAGS += -ftracer
#	LIB_CFLAGS += -fstrength-reduce
	LIB_CFLAGS += -fomit-frame-pointer
else
	LIB_CFLAGS += -DENABLE_PROFILE
	LIB_CFLAGS += -pg
endif

# $(shell $(SDL_CONFIG) --cflags)
###
#CXXFLAGS += $(CFLAGS)
#CXXFLAGS += -fno-exceptions
#CXXFLAGS += -fno-rtti
#CXXFLAGS += -fsingle-precision-constant
#CXXFLAGS += -mno-check-zero-division
###
#CXXFLAGS += $(CFLAGS)
#CXXFLAGS += -fno-exceptions
#CXXFLAGS += -fno-rtti
###
#CXXFLAGS += -fno-builtin-printf
###
#ASFLAGS = $(CFLAGS)

CXXFLAGS += $(CFLAGS)
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti



#------------------------------------------------------------------------------
# build.mak.
#------------------------------------------------------------------------------

include $(PSPSDK)/lib/build.mak

#---------------------------------------------------------------------
# Rules to make libraries.
#---------------------------------------------------------------------
# 何でか知らないけど、ライブラリ(*.a)については、
# include 先の *.mak に書くと Makefile がやってくれないので、ここに書く。
#---------------------------------------------------------------------

# build ogg lib.
#$(OBJ)/libtremor/lib_mohou_vorbisidec.a: $(TREMOR_OBJS)
$(OBJ)/$(LIBTREMOR_DIR)/lib_mohou_vorbisidec.a: $(TREMOR_OBJS)

# build vfpu lib.
$(OBJ)/vfpu/lib_mohou_vfpu.a: $(LIB_PSP_MATH_OBJS)

# build gu lib.
$(OBJ)/libgu/libgu_tiny.a: $(LIB_PSP_GU_OBJS)

# build debug lib.
$(OBJ)/debug/debug.a: $(LIB_PSP_DEBUG_OBJS)

#---------------------------------------------------------------------
# Rules to manage files.
#---------------------------------------------------------------------

# malloc free で warnings.
#$(OBJ)/jpeg/%.o: $(SRC)/jpeg/%.c
#	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) -c $< -o $@

# malloc free で warnings.
#$(OBJ)/libpng/%.o: $(SRC)/libpng/%.c
#	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) -c $< -o $@

# malloc free で warnings.
#$(OBJ)/SDL_image/IMG_png.o: $(SRC)/SDL_image/IMG_png.c
#	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) -c $< -o $@


#rc/libtremor/misc.h(209) : warning: implicit declaration of function '_ilog'
#rc/libtremor/misc.h(209) : warning: implicit declaration of function 'abs'
#	で warnings

# CPPゲームコアの場合c++(ライブラリとgnuプロファイラの扱いを変える)。
#$(OBJ)/game_core/%.o: $(SRC)/game_core/%.cpp
#	psp-gcc $(CFLAGS_OPTIMIZE)  $(CXXFLAGS) $(CORE_CFLAGS) -c $< -o $@

# 取り敢えず smpeg (バグ抜けるまで氷結)アンサポート中。
# MP3ライブラリの場合(c++ なのは、 smpeg だけ)
#$(OBJ)/%.o: $(SRC)/%.cpp
#	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CXXFLAGS) $(LIB_CFLAGS) -c $< -o $@

# OGGの場合( alloca(); で warnings )。
#$(OBJ)/libtremor/%.o: $(SRC)/libtremor/%.c
$(OBJ)/$(LIBTREMOR_DIR)/%.o: $(SRC)/$(LIBTREMOR_DIR)/%.c
	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# Cゲームコアの場合(ライブラリとgnuプロファイラの扱いを変える)。
$(OBJ)/game_core/%.o: $(SRC)/game_core/%.c
	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) $(OPTION_CFLAGS) $(CORE_CFLAGS) -c $< -o $@

# 旧pngの場合。
#$(OBJ)/png/%.o: $(SRC)/png/%.c
#	psp-gcc -O2 -Werror $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# audio_mixerの場合。
$(OBJ)/PSPL/audio/mixer/%.o: $(SRC)/PSPL/audio/mixer/%.c
	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# てすとのライブラリの場合。
#$(OBJ)/SDL231/video/%.o: $(SRC)/SDL231/video/%.c
#	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# エラーが出るのでとりあえず。(???????)。
#$(OBJ)/PSPL/video/PSPL_pspvideo.o: $(SRC)/PSPL/video/PSPL_pspvideo.c
#	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# エラーが出るのでとりあえず。
$(OBJ)/PSPL/video/PSPL_bmp.o: $(SRC)/PSPL/video/PSPL_bmp.c
	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# エラーが出るのでとりあえず。(???????)。
$(OBJ)/PSPL/video/PSPL_video.o: $(SRC)/PSPL/video/PSPL_video.c
	psp-gcc $(CFLAGS_OPTIMIZE) $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@


# その他のライブラリの場合。
$(OBJ)/%.o: $(SRC)/%.c
	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

# アセンブラの場合。
$(OBJ)/%.o: $(SRC)/%.S
	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) $(LIB_CFLAGS) -c $< -o $@

#	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CFLAGS) -c $< -o $@
#	psp-gcc $(CFLAGS_OPTIMIZE) -Werror $(CXXFLAGS) -c $< -o $@

# ライブラリをアーカイブ(組み立てる)する場合。(アーカイブ==無圧縮の書庫を作成する)
$(OBJ)/%.a:
	@echo Archiving $@...
	@$(AR) -r $@ $^



#cc1: warnings being treated as errors
#src/PSPL/video/PSPL_pspvideo.c: In function 'vidmem_alloc':
#src/PSPL/video/PSPL_pspvideo.c(187) : warning: cast from function call of type 'void *' to non-matching type 'long unsigned int'
#src/PSPL/video/PSPL_pspvideo.c: In function 'PSP_GuStretchBlit':
#src/PSPL/video/PSPL_pspvideo.c(278) : warning: pointer of type 'void *' used in arithmetic
#src/PSPL/video/PSPL_pspvideo.c(285) : warning: pointer of type 'void *' used in arithmetic
#src/PSPL/video/PSPL_pspvideo.c(286) : warning: pointer of type 'void *' used in arithmetic
#src/PSPL/video/PSPL_pspvideo.c(313) : warning: pointer of type 'void *' used in arithmetic
#src/PSPL/video/PSPL_pspvideo.c: In function 'PSP_VideoQuit':
#src/PSPL/video/PSPL_pspvideo.c(615) : warning: pointer of type 'void *' used in arithmetic
#make: *** [obj/PSPL/video/PSPL_pspvideo.o] Error 1


#cc1.exe: warnings being treated as errors
#src/PSPL/video/PSPL_pspvideo.c: In function 'vidmem_alloc':
#src/PSPL/video/PSPL_pspvideo.c:167: error: cast from function call of type 'void *' to non-matching type 'long unsigned int'
#C:\PSPSDK\BIN\MAKE.EXE: *** [obj/PSPL/video/PSPL_pspvideo.o] Error 1


#------------------------------------------------------------------------------
# Utilities.
#------------------------------------------------------------------------------
# cygwin: windows下で仮想unixを動作させるツール。遅いと評判^^;。

#(ここはTAB入れて字下げ出来ないので注意)
#ifeq ($(PSPDEV),)
# Minimalist ???
#else
# 0==通常開発(cygwin)
#endif

ifneq ($(USE_MINIMALIST_PSP_SDK),1)
# 通常開発(cygwin)
# (unix:ディレクトリー ,msdos: ディレクトリー ,windows: フォルダ)[OSで名称が違うが同じ物]
# make directory (unix:mkdir ,msdos:md) メイク-ディアー、メイク-ディレクトリー(ディレクトリを作成する)
#435ではbuild.mak内にある。MKDIR = mkdir.exe
RM = -rm
# copy    (unix:cp ,msdos: copy) コピー(ファイルを複製する)[2つに増える]
#435ではbuild.mak内にある。CP = cp
CP = cp
# re-move (unix:rm ,msdos:del)  リムーブ(ファイルを消す)
#435ではbuild.mak内にある。RM = rm
# move    (unix:mv ,msdos:move)  ムーブ(ファイルを移動する)[移動元は削除される]
MV = mv
# archiver ア－カイバ(C言語などのコンパイルした.objファイルをライブラリ.aファイルに纏めたり分解したりするツール。ファイル圧縮は一切しない)
#435ではbuild.mak内にある。(psp-ar)AR = ar
else
# pspsdk-setup-0.11.1
#Minimalist PSP homebrew SDK for Windows.(以下Minimalistと略)
# こっちは知らない(たぶんMinimalistはこっち)
# Minimalistは実際中身cygwin(の簡略版)で動いてるから、大体一緒。
# ただ、make.exe とか 速度要る奴はcygwin関係無くてnativeで動いてるっぽい。
#MKDIR = -mkdir
#RM = -rm
MKDIR = mkdir
#RM = -rm.exe
RM = rm
#MV = mv
endif

# 自動で obj ディレクトリを作成する機能。
mk_dir:
	@echo Making directry for $(TARGET) ...
	@$(MKDIR) -p $(subst //,\,$(sort $(OBJDIRS)))
	@$(RM) -f PARAM.SFO

ifneq ($(USE_MINIMALIST_PSP_SDK),1)
# 通常開発(cygwin)
DELTREE_OBJ_ALL 	= @$(RM) -f -rd $(OBJ)
DELTREE_AUDIO_MIXER	= @$(RM) -f -rd $(OBJ)/audio_mixer
DELTREE_OBJ_CORE	= @$(RM) -f -rd $(OBJ)/game_core
DELTREE_OBJ_JIKI	= @$(RM) -f -rd $(OBJ)/game_core/jiki
else
# pspsdk-setup-0.11.1
DELTREE_OBJ_ALL 	= $(RM) -f -r -d $(OBJ)
DELTREE_AUDIO_MIXER	= $(RM) -f -r -d $(OBJ)/audio_mixer
DELTREE_OBJ_CORE	= $(RM) -f -r -d $(OBJ)/game_core
DELTREE_OBJ_JIKI	= $(RM) -f -r -d $(OBJ)/game_core/jiki
#C:\pspsdk\srcr34>rm --help
#Usage: C:\PSPSDK\BIN\RM.EXE [OPTION]... FILE...
#Remove (unlink) the FILE(s).
#
#  -d, --directory       unlink directory, even if non-empty (super-user only)
#  -f, --force           ignore nonexistent files, never prompt
#  -i, --interactive     prompt before any removal
#  -r, -R, --recursive   remove the contents of directories recursively
#  -v, --verbose         explain what is being done
#      --help            display this help and exit
#      --version         output version information and exit
#
# うちではディレクトリ消去しようとするとどんな指定でも No such file or directory になる。
# C:\PSPSDK\BIN\RM.EXE に関しては、うちでは正常動作しない為不明。
endif


# audio mixer のみ、リコンパイル用。
# Make mixer ↓ (但しcygwin)
mixer:
	@echo Remove audio mixer files.
	@$(DELTREE_AUDIO_MIXER)

# ゲームコアのみ、リコンパイル用。
# Make core ↓ (但しcygwin)
core:
	@echo Remove shooting core files.
	@$(DELTREE_OBJ_CORE)

# ゲームコア自機のみ、リコンパイル用。
# Make jiki ↓ (但しcygwin)
jiki:
	@echo Remove shooting core jiki files.
	@$(DELTREE_OBJ_JIKI)

# あたり判定デバッグ機能、リコンパイル用。(game_main.hで設定)
# Make a ↓ (但しcygwin)
a:
	@echo Remove atari debug files.
	@$(RM) -f $(OBJ)/game_core/jiki/jiki.o
	@$(RM) -f $(OBJ)/game_core/jiki/jiki_shot.o
	@$(RM) -f $(OBJ)/game_core/jiki/jiki_bomber.o
	@$(RM) -f $(OBJ)/game_core/my_math.o
	@$(RM) -f $(OBJ)/game_core/sprite_bullet.o
	@$(RM) -f $(OBJ)/game_core/score_panel.o

#	@$(RM) -f $(OBJ)/game_core/*.o
#	@$(RM) -f $(OBJ)/game_core/boss/*.o
#	@$(RM) -f $(OBJ)/game_core/douchu/*.o
#	@$(RM) -f $(OBJ)/game_core/draw/*.o
#	@$(RM) -f $(OBJ)/game_core/menu/*.o
#	@$(RM) -f $(OBJ)/game_core/tama/*.o

# syomei banをminimalistでやる場合のパッチ。
patch:
	@echo syomei ban minimalist patch.
	@$(RM) -f $(OBJ)/game_core/boot_main.o
	@$(RM) -f $(TARGET).prx
	@$(RM) -f $(TARGET).elf
	@$(RM) -f PARAM.SFO
	@$(RM) -f EBOOT.PBP


# gu 作りなおしたい場合に。
# Make gu ↓ (但しcygwin)
gu:
	@echo Remove custom font files.
	@$(RM) -f $(OBJ)/game_core/draw/*.o

# font 作りなおしたい場合に。
# Make font ↓ (但しcygwin)
font:
	@echo Remove custom font files.
	@$(RM) -f $(OBJ)/font/*.o


# とにかく全部 obj 削除したい場合に。
# Make rr ↓ (但しcygwin)  (rr は Remove all object for Release.のつもり)
rr:
	@echo Remove all temporaly files.
	@$(RM) -f PARAM.SFO
	@$(RM) -f *.elf
	@$(RM) -f $(TARGET)_map.txt
	@$(DELTREE_OBJ_ALL)
