export module resource;

import core;
import dx;

export class Resource
{
public:
    virtual ~Resource();

    ID3D12Resource* InternalResource;
};