#ifndef DLOG_H_
#define DLOG_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

class dlog_t : public kaitai::kstruct {

public:
    class header_t;
    class data_t;

    enum formats_t {
        FORMATS_OPENSCOPE = 1,
        FORMATS_OPENLOGGER = 3
    };

    enum stop_reasons_t {
        STOP_REASONS_NORMAL = 0,
        STOP_REASONS_FORCED = 1,
        STOP_REASONS_ERROR = 2,
        STOP_REASONS_OVERFLOW = 3,
        STOP_REASONS_UNKNOWN = 4
    };

    dlog_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, dlog_t* p__root = 0);

private:
    void _read();

public:
    ~dlog_t();

    class header_t : public kaitai::kstruct {

    public:

        header_t(kaitai::kstream* p__io, dlog_t* p__parent = 0, dlog_t* p__root = 0);

    private:
        int m__is_le;

    public:

    private:
        void _read();

    public:

    private:
        void _read_le();

    public:

    private:
        void _read_be();

    public:
        ~header_t();

    private:
        bool f_sample_rate;
        double m_sample_rate;

    public:

        /**
         * calculated sample rate
         */
        double sample_rate();

    private:
        bool f_delay;
        double m_delay;

    public:

        /**
         * calculated delay
         */
        double delay();

    private:
        uint8_t m_bytes_per_sample;
        uint16_t m_header_length;
        uint16_t m_header_size;
        formats_t m_format;
        uint32_t m_revision;
        uint64_t m_voltage_scale;
        stop_reasons_t m_stop_reason;
        uint64_t m_start_index;
        uint64_t m_sample_count;
        uint64_t m_sample_rate_scale;
        uint64_t m_sample_rate_raw;
        uint64_t m_delay_scale;
        uint64_t m_delay_raw;
        uint32_t m_channels_per_sample;
        bool n_channels_per_sample;

    public:
        bool _is_null_channels_per_sample() { channels_per_sample(); return n_channels_per_sample; };

    private:
        std::vector<uint8_t>* m_channel_map;
        bool n_channel_map;

    public:
        bool _is_null_channel_map() { channel_map(); return n_channel_map; };

    private:
        dlog_t* m__root;
        dlog_t* m__parent;

    public:

        /**
         * Number of bytes per sample
         */
        uint8_t bytes_per_sample() const { return m_bytes_per_sample; }

        /**
         * Length of the header structure
         */
        uint16_t header_length() const { return m_header_length; }

        /**
         * The space in the file taken by the header, sector aligned (512)
         */
        uint16_t header_size() const { return m_header_size; }

        /**
         * Format of the header and potential data
         */
        formats_t format() const { return m_format; }

        /**
         * Specific header revision
         */
        uint32_t revision() const { return m_revision; }
        uint64_t voltage_scale() const { return m_voltage_scale; }

        /**
         * Reason logging stopped
         */
        stop_reasons_t stop_reason() const { return m_stop_reason; }

        /**
         * Sample index of first sample in log, usually 0
         */
        uint64_t start_index() const { return m_start_index; }

        /**
         * Number of samples in the log
         */
        uint64_t sample_count() const { return m_sample_count; }

        /**
         * Sample rate scale
         */
        uint64_t sample_rate_scale() const { return m_sample_rate_scale; }

        /**
         * Raw sample rate
         */
        uint64_t sample_rate_raw() const { return m_sample_rate_raw; }

        /**
         * Delay scale
         */
        uint64_t delay_scale() const { return m_delay_scale; }

        /**
         * Delay from start of sampling until the first sample was taken, usually 0
         */
        uint64_t delay_raw() const { return m_delay_raw; }

        /**
         * How many channels in per sample
         */
        uint32_t channels_per_sample() const { return m_channels_per_sample; }

        /**
         * the channel order
         */
        std::vector<uint8_t>* channel_map() const { return m_channel_map; }
        dlog_t* _root() const { return m__root; }
        dlog_t* _parent() const { return m__parent; }
    };

    class data_t : public kaitai::kstruct {

    public:
        class sample_t;

        data_t(kaitai::kstream* p__io, dlog_t* p__parent = 0, dlog_t* p__root = 0);

    private:
        int m__is_le;

    public:

    private:
        void _read();

    public:

    private:
        void _read_le();

    public:

    private:
        void _read_be();

    public:
        ~data_t();

        class sample_t : public kaitai::kstruct {

        public:

            sample_t(kaitai::kstream* p__io, dlog_t::data_t* p__parent = 0, dlog_t* p__root = 0, int p_is_le = -1);

        private:
            int m__is_le;

        public:

        private:
            void _read();

        public:

        private:
            void _read_le();

        public:

        private:
            void _read_be();

        public:
            ~sample_t();

        private:
            std::vector<int32_t>* m_channel;
            bool n_channel;

        public:
            bool _is_null_channel() { channel(); return n_channel; };

        private:
            dlog_t* m__root;
            dlog_t::data_t* m__parent;

        public:
            std::vector<int32_t>* channel() const { return m_channel; }
            dlog_t* _root() const { return m__root; }
            dlog_t::data_t* _parent() const { return m__parent; }
        };

    private:
        std::vector<sample_t*>* m_samples;
        dlog_t* m__root;
        dlog_t* m__parent;

    public:
        std::vector<sample_t*>* samples() const { return m_samples; }
        dlog_t* _root() const { return m__root; }
        dlog_t* _parent() const { return m__parent; }
    };

private:
    bool f_data;
    data_t* m_data;

public:
    data_t* data();

private:
    uint8_t m_endianness;
    header_t* m_header;
    dlog_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Endianness of the log file. 0 for little endian, 1 for big endian
     */
    uint8_t endianness() const { return m_endianness; }
    header_t* header() const { return m_header; }
    dlog_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // DLOG_H_
