#include "framebuffer.h"
#include "framebuffer_attachment.h"
#include "../utils/stl_utils.h"


GLenum gle::gl_color_attachment(int idx)
{
    return GL_COLOR_ATTACHMENT0 + idx;
}

char const * gle::framebuffer_completeness_str(framebuffer_completeness_t fc)
{
    switch (fc)
    {
    case FC_complete : return "complete";
    case FC_incmoplete_layer_targets : return "incomplete layer targtes";
    case FC_incomplete_attachment : return "incomplete attachments";
    case FC_incomplete_missing_attachment : return "incomplete missing attachment";
    case FC_incomplete_multisample : return "incomplete multisample";
    case FC_undefined : return "undefined";
    case FC_unsupported : return "unsupported";
    default : return "unknown";
    }
}

namespace gle
{

struct framebuffer_t::buffers_storage_t
{
    buffers_storage_t()
        : read_buffer(-1)
    {}

    std::vector<int> draw_buffers;
    int read_buffer;
};

struct framebuffer_t::attachment_storage_t
{
    typedef std::map<GLenum, framebuffer_attachment_t> fb_attachments_map_t;

    attachment_storage_t(i_framebuffer const * fb)
        : depth(GL_DEPTH_ATTACHMENT, fb)
        , stencil(GL_STENCIL_ATTACHMENT, fb)
    {}

    fb_attachments_map_t colors;
    framebuffer_attachment_t depth;
    framebuffer_attachment_t stencil;
};

framebuffer_t::framebuffer_t(GLuint id)
    : id_(id)
    , buffers_(new buffers_storage_t())
    , attachments_(new attachment_storage_t(this))
{}

framebuffer_t::~framebuffer_t() {}

i_framebuffer_attachment * framebuffer_t::color_attachment(int idx)
{
    if (attachments_->colors.find(idx) == attachments_->colors.end())
    {
        attachments_->colors.insert(std::make_pair(idx,
            framebuffer_attachment_t(gl_color_attachment(idx), this)));
    }
    return &attachments_->colors.at(idx);
}

i_framebuffer_attachment * framebuffer_t::depth_attachment()
{
    return &attachments_->depth;
}

i_framebuffer_attachment * framebuffer_t::stencil_attachment()
{
    return &attachments_->stencil;
}

std::vector<GLenum> framebuffer_t::idx2glenums(std::vector<int> const& buffers)
{
    std::vector<GLenum> res(buffers.size());
    for (size_t i = 0; i < buffers.size(); i++)
        res[i] = gl_color_attachment(buffers[i]);
    return res;
}

void framebuffer_t::set_draw_buffers(std::vector<int> const& buffers)
{
    std::vector<GLenum> buffers_enum = idx2glenums(buffers);
    glFramebufferDrawBuffersEXT(id_, buffers_enum.size(), utils::raw_ptr(buffers_enum));
    buffers_->draw_buffers = buffers;
}

void framebuffer_t::set_read_buffer(int buffer)
{
    GLenum buffer_enum = gl_color_attachment(buffer);
    glFramebufferReadBufferEXT(id_, buffer_enum);
    buffers_->read_buffer = buffer;
}


std::vector<int> const& framebuffer_t::draw_buffers() const
{
    return buffers_->draw_buffers;
}

int framebuffer_t::read_buffer() const
{
    return buffers_->read_buffer;
}


framebuffer_completeness_t framebuffer_t::check_draw() const
{
    return framebuffer_completeness_t(glCheckNamedFramebufferStatusEXT(id_, GL_DRAW_FRAMEBUFFER));
}

framebuffer_completeness_t framebuffer_t::check_read() const
{
    return framebuffer_completeness_t(glCheckNamedFramebufferStatusEXT(id_, GL_READ_FRAMEBUFFER));
}

}
