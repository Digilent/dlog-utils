// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "dlog.h"

#include <stdexcept>

dlog_t::dlog_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, dlog_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    f_data = false;
    _read();
}

void dlog_t::_read() {
    m_endianness = m__io->read_u1();
    m_header = new header_t(m__io, this, m__root);
}

dlog_t::~dlog_t() {
    delete m_header;
    if (f_data) {
        delete m_data;
    }
}

dlog_t::header_t::header_t(kaitai::kstream* p__io, dlog_t* p__parent, dlog_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = -1;
    f_sample_rate = false;
    f_delay = false;
    _read();
}

void dlog_t::header_t::_read() {
    switch (_root()->endianness()) {
    case 0: {
        m__is_le = true;
        break;
    }
    case 1: {
        m__is_le = false;
        break;
    }
    }

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void dlog_t::header_t::_read_le() {
    m_bytes_per_sample = m__io->read_u1();
    m_header_length = m__io->read_u2le();
    m_header_size = m__io->read_u2le();
    m_format = static_cast<dlog_t::formats_t>(m__io->read_u2le());
    m_revision = m__io->read_u4le();
    m_voltage_scale = m__io->read_u8le();
    m_stop_reason = static_cast<dlog_t::stop_reasons_t>(m__io->read_u4le());
    m_start_index = m__io->read_u8le();
    m_sample_count = m__io->read_u8le();
    m_sample_rate_scale = m__io->read_u8le();
    m_sample_rate_raw = m__io->read_u8le();
    m_delay_scale = m__io->read_u8le();
    m_delay_raw = m__io->read_u8le();
    n_channels_per_sample = true;
    if (format() == FORMATS_OPENLOGGER) {
        n_channels_per_sample = false;
        m_channels_per_sample = m__io->read_u4le();
    }
    n_channel_map = true;
    if (format() == FORMATS_OPENLOGGER) {
        n_channel_map = false;
        int l_channel_map = 8;
        m_channel_map = new std::vector<uint8_t>();
        m_channel_map->reserve(l_channel_map);
        for (int i = 0; i < l_channel_map; i++) {
            m_channel_map->push_back(m__io->read_u1());
        }
    }
}

void dlog_t::header_t::_read_be() {
    m_bytes_per_sample = m__io->read_u1();
    m_header_length = m__io->read_u2be();
    m_header_size = m__io->read_u2be();
    m_format = static_cast<dlog_t::formats_t>(m__io->read_u2be());
    m_revision = m__io->read_u4be();
    m_voltage_scale = m__io->read_u8be();
    m_stop_reason = static_cast<dlog_t::stop_reasons_t>(m__io->read_u4be());
    m_start_index = m__io->read_u8be();
    m_sample_count = m__io->read_u8be();
    m_sample_rate_scale = m__io->read_u8be();
    m_sample_rate_raw = m__io->read_u8be();
    m_delay_scale = m__io->read_u8be();
    m_delay_raw = m__io->read_u8be();
    n_channels_per_sample = true;
    if (format() == FORMATS_OPENLOGGER) {
        n_channels_per_sample = false;
        m_channels_per_sample = m__io->read_u4be();
    }
    n_channel_map = true;
    if (format() == FORMATS_OPENLOGGER) {
        n_channel_map = false;
        int l_channel_map = 8;
        m_channel_map = new std::vector<uint8_t>();
        m_channel_map->reserve(l_channel_map);
        for (int i = 0; i < l_channel_map; i++) {
            m_channel_map->push_back(m__io->read_u1());
        }
    }
}

dlog_t::header_t::~header_t() {
    if (!n_channels_per_sample) {
    }
    if (!n_channel_map) {
        delete m_channel_map;
    }
}

double dlog_t::header_t::sample_rate() {
    if (f_sample_rate)
        return m_sample_rate;
    m_sample_rate = ((1.0 * sample_rate_raw()) / sample_rate_scale());
    f_sample_rate = true;
    return m_sample_rate;
}

double dlog_t::header_t::delay() {
    if (f_delay)
        return m_delay;
    m_delay = ((1.0 * delay_raw()) / delay_scale());
    f_delay = true;
    return m_delay;
}

dlog_t::data_t::data_t(kaitai::kstream* p__io, dlog_t* p__parent, dlog_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = -1;
    _read();
}

void dlog_t::data_t::_read() {
    switch (_root()->endianness()) {
    case 0: {
        m__is_le = true;
        break;
    }
    case 1: {
        m__is_le = false;
        break;
    }
    }

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void dlog_t::data_t::_read_le() {
    m_samples = new std::vector<sample_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_samples->push_back(new sample_t(m__io, this, m__root, m__is_le));
            i++;
        }
    }
}

void dlog_t::data_t::_read_be() {
    m_samples = new std::vector<sample_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_samples->push_back(new sample_t(m__io, this, m__root, m__is_le));
            i++;
        }
    }
}

dlog_t::data_t::~data_t() {
    for (std::vector<sample_t*>::iterator it = m_samples->begin(); it != m_samples->end(); ++it) {
        delete *it;
    }
    delete m_samples;
}

dlog_t::data_t::sample_t::sample_t(kaitai::kstream* p__io, dlog_t::data_t* p__parent, dlog_t* p__root, int p_is_le) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = p_is_le;
    _read();
}

void dlog_t::data_t::sample_t::_read() {

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void dlog_t::data_t::sample_t::_read_le() {
    int l_channel = ((_root()->header()->format() != FORMATS_OPENSCOPE) ? (_root()->header()->channels_per_sample()) : (1));
    m_channel = new std::vector<int32_t>();
    m_channel->reserve(l_channel);
    for (int i = 0; i < l_channel; i++) {
        n_channel = true;
        switch (_root()->header()->bytes_per_sample()) {
        case 1: {
            n_channel = false;
            m_channel->push_back(m__io->read_s1());
            break;
        }
        case 2: {
            n_channel = false;
            m_channel->push_back(m__io->read_s2le());
            break;
        }
        case 4: {
            n_channel = false;
            m_channel->push_back(m__io->read_s4le());
            break;
        }
        }
    }
}

void dlog_t::data_t::sample_t::_read_be() {
    int l_channel = ((_root()->header()->format() != FORMATS_OPENSCOPE) ? (_root()->header()->channels_per_sample()) : (1));
    m_channel = new std::vector<int32_t>();
    m_channel->reserve(l_channel);
    for (int i = 0; i < l_channel; i++) {
        n_channel = true;
        switch (_root()->header()->bytes_per_sample()) {
        case 1: {
            n_channel = false;
            m_channel->push_back(m__io->read_s1());
            break;
        }
        case 2: {
            n_channel = false;
            m_channel->push_back(m__io->read_s2be());
            break;
        }
        case 4: {
            n_channel = false;
            m_channel->push_back(m__io->read_s4be());
            break;
        }
        }
    }
}

dlog_t::data_t::sample_t::~sample_t() {
    if (!n_channel) {
        delete m_channel;
    }
}

dlog_t::data_t* dlog_t::data() {
    if (f_data)
        return m_data;
    std::streampos _pos = m__io->pos();
    m__io->seek(_root()->header()->header_size());
    m_data = new data_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_data = true;
    return m_data;
}
