meta:
    id: dlog
    file-extension:
        - dlog
        - log

seq:
    - id: endianness
      type: u1
      doc: Endianness of the log file. 0 for little endian, 1 for big endian
      -orig-id: endian

    - id: header
      type: header
      
instances:
    data:
        pos: _root.header.header_size
        type: data

types:
    header:
        meta:
            endian:
                switch-on: _root.endianness
                cases:
                    0: le
                    1: be

        seq:
            - id: bytes_per_sample
              type: u1
              -orig-id: cbSampleEntry
              doc: Number of bytes per sample

            - id: header_length
              type: u2
              -orig-id: cbHeader
              doc: Length of the header structure

            - id: header_size
              type: u2
              -orig-id: cbHeaderInFile
              doc: The space in the file taken by the header, sector aligned (512)

            - id: format
              type: u2
              enum: formats
              doc: Format of the header and potential data

            - id: revision
              type: u4
              doc: Specific header revision

            - id: voltage_scale
              type: u8
              -orig-id: voltageUnits

            - id: stop_reason
              type: u4
              enum: stop_reasons
              -orig-id: stopReason
              doc: Reason logging stopped

            - id: start_index
              type: u8
              -orig-id: iStart
              doc: Sample index of first sample in log, usually 0

            - id: sample_count
              type: u8
              -orig-id: actualCount
              doc: Number of samples in the log

            - id: sample_rate_scale
              type: u8
              -orig-id: sampleFreqUnits
              doc: Sample rate scale 

            - id: sample_rate
              type: u8
              -orig-id: xSPS
              doc: Raw sample rate

            - id: delay_scale
              type: u8
              -orig-id: delayUnits
              doc: Delay scale

            - id: start_delay
              type: u8
              -orig-id: xDelay
              doc: Delay from start of sampling until the first sample was taken, usually 0

            - id: channels_per_sample
              if: format == formats::openlogger
              type: u4
              -orig-id: cChannels
              doc: How many channels in per sample

            - id: channel_map
              if: format == formats::openlogger
              type: u1
              repeat: expr
              repeat-expr: 8
              -orig-id: rgChannels
              doc: The channel order

        instances:
            sample_rate_hz:
                value: 1.0 * sample_rate / sample_rate_scale
                doc: Calculated sample rate 

            start_delay_sec:
                value: 1.0 * start_delay / delay_scale
                doc: Calculated delay
    
    data:
        meta:
            endian:
                switch-on: _root.endianness
                cases:
                    0: le
                    1: be
        seq:
            - id: samples
              type: sample
              repeat: eos
        
        types:
            sample:
                seq:
                    - id: channel
                      type:
                        switch-on: _root.header.bytes_per_sample
                        cases:
                            1: s1
                            2: s2
                            4: s4
                      repeat: expr
                      repeat-expr: '_root.header.format != formats::openscope ? _root.header.channels_per_sample : 1'

enums:
    formats:
        1: openscope
        3: openlogger
    
    stop_reasons:
        0: normal
        1: forced
        2: error
        3: overflow
        4: unknown
