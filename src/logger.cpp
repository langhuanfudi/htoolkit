#include "logger.h"

using namespace std;

namespace htoolkit {
logger* g_defaultLogger = nullptr;

logger& getlogger() {
	if (g_defaultLogger == nullptr) {
		g_defaultLogger = &logger::Instance();
	}
	return *g_defaultLogger;
}

INSTANCE_IMP(logger, exeName());

} // namespace htoolkit
