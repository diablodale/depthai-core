#pragma once

#include <assert.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "../host_data_packet.hpp"
#include "tensor_entry.hpp"
#include "tensor_entry_container.hpp"
#include "tensor_info.hpp"

class NNetPacket {
   public:
    NNetPacket(std::vector<std::shared_ptr<HostDataPacket>>& tensors_raw_data, const std::vector<TensorInfo>& tensors_info)
        : _tensors_raw_data(tensors_raw_data), _tensors_info(&tensors_info), _tensor_entry_container(new TensorEntryContainer(tensors_raw_data, tensors_info)) {
        for(size_t i = 0; i < tensors_info.size(); ++i) {
            _tensor_name_to_index[tensors_info.at(i).output_tensor_name] = i;
        }

        if(_tensor_name_to_index.size() != tensors_info.size()) {
            printf("There are duplication in tensor names!\n");
        }
    }

    std::shared_ptr<TensorEntryContainer> getTensorEntryContainer() {
        return _tensor_entry_container;
    }

    boost::optional<FrameMetadata> getMetadata() {
        // TODO
        return _tensors_raw_data[0]->getMetadata();
    }

   protected:
    std::vector<std::shared_ptr<HostDataPacket>> _tensors_raw_data;
    const std::vector<TensorInfo>* _tensors_info = nullptr;
    std::shared_ptr<TensorEntryContainer> _tensor_entry_container;
    std::unordered_map<std::string, unsigned> _tensor_name_to_index;
};
