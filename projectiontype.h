#ifndef PROJECTIONTYPE_H
#define PROJECTIONTYPE_H

#include <QMetaEnum>

enum class ProjectionType
{
	Orthographic,
	Perspective
};

Q_DECLARE_METATYPE(ProjectionType)

#endif // PROJECTIONTYPE_H
