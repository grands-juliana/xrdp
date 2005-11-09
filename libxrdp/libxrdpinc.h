/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   xrdp: A Remote Desktop Protocol server.
   Copyright (C) Jay Sorg 2004-2005

   header file for use with libxrdp.so / xrdp.dll

*/

#if !defined(LIBXRDPINC_H)
#define LIBXRDPINC_H

struct xrdp_client_info
{
  int bpp;
  int width;
  int height;
  int cache1_entries;
  int cache1_size;
  int cache2_entries;
  int cache2_size;
  int cache3_entries;
  int cache3_size;
  int pointer_cache_entries;
  int use_bitmap_comp;
  int use_bitmap_cache;
  int op1; /* use smaller bitmap header, non cache */
  int op2; /* use smaller bitmap header in bitmap cache */
  int desktop_cache;
  int use_compact_packets; /* rdp5 smaller packets */
  char hostname[32];
  int build;
  int keylayout;
  char username[256];
  char password[256];
  char domain[256];
  char program[256];
  char directory[256];
  int rdp_compression;
  int rdp_autologin;
};

struct xrdp_brush
{
  int x_orgin;
  int y_orgin;
  int style;
  char pattern[8];
};

struct xrdp_pen
{
  int style;
  int width;
  int color;
};

struct xrdp_font_char
{
  int offset;
  int baseline;
  int width;
  int height;
  int incby;
  char* data;
};

struct xrdp_rect
{
  int left;
  int top;
  int right;
  int bottom;
};

struct xrdp_session
{
  long id;
  int sck;
  int term; /* do we need this */
  int (*callback)(long id, int msg, long param1, long param2, long param3,
                  long param4);
  void* rdp;
  void* orders;
  struct xrdp_client_info* client_info;
  int up_and_running;
  struct stream* s;
};

struct xrdp_session* DEFAULT_CC
libxrdp_init(long id, int sck);
int DEFAULT_CC
libxrdp_exit(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_disconnect(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_process_incomming(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_process_data(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_send_palette(struct xrdp_session* session, int* palette);
int DEFAULT_CC
libxrdp_send_bitmap(struct xrdp_session* session, int width, int height,
                    int bpp, char* data, int x, int y, int cx, int cy);
int DEFAULT_CC
libxrdp_send_pointer(struct xrdp_session* session, int cache_idx,
                     char* data, char* mask, int x, int y);
int DEFAULT_CC
libxrdp_set_pointer(struct xrdp_session* session, int cache_idx);
int DEFAULT_CC
libxrdp_orders_init(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_orders_send(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_orders_force_send(struct xrdp_session* session);
int DEFAULT_CC
libxrdp_orders_rect(struct xrdp_session* session, int x, int y,
                    int cx, int cy, int color, struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_screen_blt(struct xrdp_session* session, int x, int y,
                          int cx, int cy, int srcx, int srcy,
                          int rop, struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_pat_blt(struct xrdp_session* session, int x, int y,
                       int cx, int cy, int rop, int bg_color,
                       int fg_color, struct xrdp_brush* brush,
                       struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_dest_blt(struct xrdp_session* session, int x, int y,
                        int cx, int cy, int rop,
                        struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_line(struct xrdp_session* session, int mix_mode,
                    int startx, int starty,
                    int endx, int endy, int rop, int bg_color,
                    struct xrdp_pen* pen,
                    struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_mem_blt(struct xrdp_session* session, int cache_id,
                       int color_table, int x, int y, int cx, int cy,
                       int rop, int srcx, int srcy,
                       int cache_idx, struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_text(struct xrdp_session* session,
                    int font, int flags, int mixmode,
                    int fg_color, int bg_color,
                    int clip_left, int clip_top,
                    int clip_right, int clip_bottom,
                    int box_left, int box_top,
                    int box_right, int box_bottom,
                    int x, int y, char* data, int data_len,
                    struct xrdp_rect* rect);
int DEFAULT_CC
libxrdp_orders_send_palette(struct xrdp_session* session, int* palette,
                            int cache_id);
int DEFAULT_CC
libxrdp_orders_send_raw_bitmap(struct xrdp_session* session,
                               int width, int height, int bpp, char* data,
                               int cache_id, int cache_idx);
int DEFAULT_CC
libxrdp_orders_send_bitmap(struct xrdp_session* session,
                           int width, int height, int bpp, char* data,
                           int cache_id, int cache_idx);
int DEFAULT_CC
libxrdp_orders_send_font(struct xrdp_session* session,
                         struct xrdp_font_char* font_char,
                         int font_index, int char_index);
int DEFAULT_CC
libxrdp_reset(struct xrdp_session* session,
              int width, int height, int bpp);

#endif