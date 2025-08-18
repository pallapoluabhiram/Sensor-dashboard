#include "ImageProviderWrapper.h"

ImageProviderWrapper::ImageProviderWrapper(ImageProvider* provider, QObject *parent)
    : QObject(parent)
    , m_provider(provider)
{
}

void ImageProviderWrapper::setPlaybackMode(bool enabled)
{
    if (m_provider) {
        m_provider->setPlaybackMode(enabled);
    }
}
