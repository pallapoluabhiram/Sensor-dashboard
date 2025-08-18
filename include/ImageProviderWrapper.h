#pragma once

#include <QObject>
#include "ImageProvider.h"

class ImageProviderWrapper : public QObject
{
    Q_OBJECT

public:
    explicit ImageProviderWrapper(ImageProvider* provider, QObject *parent = nullptr);

    Q_INVOKABLE void setPlaybackMode(bool enabled);

private:
    ImageProvider* m_provider;
};
