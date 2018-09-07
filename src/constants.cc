/*
 * Copyright 2018, Niels Ole Salscheider
 *
 * This file is part of Babilas.
 *
 * Babilas is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Babilas is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Babilas. If not, see <https://www.gnu.org/licenses/>.
 */

#include "constants.hh"

namespace Constants {
const QLatin1String applicationName("Babilas");
const QLatin1String organizationName("Babilas");
} // namespace Constants

namespace DebugCategories {
Q_LOGGING_CATEGORY(qxmppGeneric, "qxmpp.generic")
Q_LOGGING_CATEGORY(qxmppStanza, "qxmpp.stanza")
Q_LOGGING_CATEGORY(general, "babilas.general")
Q_LOGGING_CATEGORY(tracing, "babilas.tracing")
} // namespace DebugCategories
