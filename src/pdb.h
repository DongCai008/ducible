/*
 * Copyright (c) 2016 Jason White
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <stdlib.h>
#include <stdint.h>

/**
 * PDB stream IDs.
 */
namespace PdbStreamType {

    // Stream table stream.
    const size_t streamTable = 0;

    // Version information, and information to connect this PDB to the EXE.
    const size_t header = 1;

    // Type information stream. All the types used in the executable.
    const size_t tbi = 2;

    // Debug information stream. Holds section contributions, and list of
    // ‘Mods’.
    const size_t dbi = 3;

    // ID info stream. Holds a hashed string table.
    const size_t ipi = 4;

    // There are more streams than this, but they are not accessed directly by a
    // stream ID constant. We are usually only interested in the above streams
    // anyway.
}

/**
 * Implementation version of the PDB.
 */
namespace PdbVersion {
    const uint32_t vc2     = 19941610;
    const uint32_t vc4     = 19950623;
    const uint32_t vc41    = 19950814;
    const uint32_t vc50    = 19960307;
    const uint32_t vc98    = 19970604;
    const uint32_t vc70Dep = 19990604; // deprecated vc70 implementation version
    const uint32_t vc70    = 20000404;
    const uint32_t vc80    = 20030901;
    const uint32_t vc110   = 20091201;
    const uint32_t vc140   = 20140508;
}

/**
 * PDB stream.
 */
struct PdbStream {
    // Implementation version number.
    uint32_t version;

    // Timestamp of when the PDB was created.
    uint32_t timestamp;

    // Number of times this PDB instance has been updated.
    uint32_t age;
};

/**
 * PDB 7.0 stream.
 */
struct PdbStream70 : public PdbStream {
    // PDB GUID. This must match the PE file.
    uint8_t sig70[16];
};

/**
 * Thrown when a PDB is found to be invalid or unsupported.
 */
class InvalidPdb
{
private:
    const char* _why;

public:

    InvalidPdb(const char* why) : _why(why) {}

    const char* why() const {
        return _why;
    }
};