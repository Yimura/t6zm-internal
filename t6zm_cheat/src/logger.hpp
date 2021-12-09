#pragma once
#include <cstring>
#include <mutex>
#include <sstream>

namespace t6zm
{
#define LOG_ARGS template <typename ...Args>
    class Logger;
    inline Logger* g_log {};

    class Logger
    {
        std::vector<std::unique_ptr<char[]>> m_messages;

        std::filesystem::path m_file_path;
        std::ofstream m_file_out;

    public:
        enum class LogLevel {
            Verbose,
            Info,
            Warning,
            Error,
            Critical
        };

        explicit Logger(LogLevel log_level) :
            m_file_path(std::getenv("appdata")),
            m_log_level(log_level)
        {
            m_file_path /= "t6zm_cheat";
            std::filesystem::path m_backup_path = m_file_path;
            m_backup_path /= "backup";

            try
            {
                if (!std::filesystem::exists(m_file_path))
                {
                    std::filesystem::create_directory(m_file_path);
                }
                else if (!std::filesystem::is_directory(m_file_path))
                {
                    std::filesystem::remove(m_file_path);
                    std::filesystem::create_directory(m_file_path);
                }
                if (!std::filesystem::exists(m_backup_path))
                {
                    std::filesystem::create_directory(m_backup_path);
                }
                else if (!std::filesystem::is_directory(m_backup_path))
                {
                    std::filesystem::remove(m_backup_path);
                    std::filesystem::create_directory(m_backup_path);
                }

                m_file_path /= "t6zm_cheat.log";

                if (std::filesystem::exists(m_file_path))
                    std::filesystem::copy_file(m_file_path, m_backup_path / "old_t6zm_cheat.log", std::filesystem::copy_options::overwrite_existing);

                m_file_out.open(m_file_path, std::ios_base::out | std::ios_base::trunc);
            }
            catch (std::filesystem::filesystem_error const& error)
            {
                this->critical("LOGGER", "Exception:\n%s", error.what());
            }

            g_log = this;
        }

        ~Logger()
        {
            g_log = nullptr;
        }

        LOG_ARGS
        void critical(const char* service, const char* format, Args&& ...args)
        {
            this->log(LogLevel::Critical, service, format, std::forward<Args>(args)...);
        }

        LOG_ARGS
        void error(const char* service, const char* format, Args&& ...args)
        {
            this->log(LogLevel::Error, service, format, std::forward<Args>(args)...);
        }

        LOG_ARGS
        void info(const char* service, const char* format, Args&& ...args)
        {
            this->log(LogLevel::Info, service, format, std::forward<Args>(args)...);
        }

        LOG_ARGS
        void verbose(const char* service, const char* format, Args&& ...args)
        {
            this->log(LogLevel::Verbose, service, format, std::forward<Args>(args)...);
        }

        LOG_ARGS
        void warning(const char* service, const char* format, Args&& ...args)
        {
            this->log(LogLevel::Warning, service, format, std::forward<Args>(args)...);
        }

        std::pair<std::unique_ptr<char[]>*, std::size_t> get_messages()
        {
            return std::make_pair(m_messages.data(), m_messages.size());
        }

        void set_log_level(LogLevel level)
        {
            this->m_log_level = level;
        }

    private:
        LogLevel m_log_level;

        LOG_ARGS
        void log(LogLevel level, const char* service, const char* format, Args&& ...args)
        {
            const size_t alloc_size = 8;
            char level_string[alloc_size];

            switch (level)
            {
            case LogLevel::Verbose:
                strcpy(level_string, "VERB");

                break;
            case LogLevel::Info:
                strcpy(level_string, "INFO");

                break;
            case LogLevel::Warning:
                strcpy(level_string, "WARN");

                break;
            case LogLevel::Error:
                strcpy(level_string, "ERR");

                break;
            case LogLevel::Critical:
                strcpy(level_string, "CRIT");

                break;
            }

            size_t size_needed = snprintf(nullptr, 0, format, std::forward<Args>(args)...) + 1;
            char* message = (char*)malloc(sizeof(char) * size_needed);
            sprintf(message, format, std::forward<Args>(args)...);

            std::stringstream sstream;
            sstream << "[" << level_string << "/" << service << "] " << message << std::endl;

            const std::string msg = sstream.str();
            size_t size = msg.length() + 1;

            m_file_out << msg << std::flush;

            auto log = std::make_unique<char[]>(size);

            std::uninitialized_fill_n(log.get(), size, '\0');
            strcpy(log.get(), msg.c_str());

            m_messages.push_back(
                std::move(log)
            );

            // be a good boy and free memory
            free(message);
            message = nullptr;
        }
    };
}