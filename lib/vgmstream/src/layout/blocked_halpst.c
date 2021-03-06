#include "layout.h"
#include "../vgmstream.h"

/* set up for the block at the given offset */
void block_update_halpst(off_t block_offset, VGMSTREAM * vgmstream) {
    int i, header_length;
    /* header length must be a multiple of 0x20 */
    header_length = (4+8*vgmstream->channels+0x1f)/0x20*0x20;
    vgmstream->current_block_offset = block_offset;
    vgmstream->current_block_size = read_32bitBE(
            vgmstream->current_block_offset,
            vgmstream->ch[0].streamfile)/vgmstream->channels;
    vgmstream->next_block_offset = read_32bitBE(
            vgmstream->current_block_offset+8,
            vgmstream->ch[0].streamfile);

    for (i=0;i<vgmstream->channels;i++) {
        vgmstream->ch[i].offset = vgmstream->current_block_offset +
            header_length + vgmstream->current_block_size*i;
    }
}
