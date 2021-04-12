#pragma once

#include <Common/config.h>

#if USE_HDFS
#include <IO/ReadBuffer.h>
#include <IO/BufferWithOwnMemory.h>
#include <string>
#include <memory>
#include <hdfs/hdfs.h> // Y_IGNORE
#include <common/types.h>
#include <Interpreters/Context.h>
#include <IO/SeekableReadBuffer.h>


namespace DB
{

/** Accepts HDFS path to file and opens it.
 * Closes file by himself (thus "owns" a file descriptor).
 */
class ReadBufferFromHDFS : public BufferWithOwnMemory<SeekableReadBuffer>
{

public:
    ReadBufferFromHDFS(const std::string & hdfs_name_, const Poco::Util::AbstractConfiguration &, size_t buf_size_ = DBMS_DEFAULT_BUFFER_SIZE);

    ~ReadBufferFromHDFS() override;

    bool nextImpl() override;

    off_t seek(off_t offset_, int whence) override;

    off_t getPosition() override;

private:
    struct ReadBufferFromHDFSImpl;
    std::unique_ptr<ReadBufferFromHDFSImpl> impl;
};
}
#endif