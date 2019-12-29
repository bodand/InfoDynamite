//
// Created by tudom on 2019-12-22.
//

#include "libnm/nm.hpp"

#include <windows.h>
#include <imagehlp.h>

std::vector <std::string> libnm::detail::ListExports(std::string_view file) noexcept {
    std::vector <std::string> ret{};

    DWORD* dNameRVAs{nullptr};
    _IMAGE_EXPORT_DIRECTORY* ImageExportDirectory;
    unsigned long cDirSize;
    _LOADED_IMAGE LoadedImage;
    if (MapAndLoad(file.data(), nullptr, &LoadedImage, TRUE, TRUE)) {
        ImageExportDirectory =
               static_cast<_IMAGE_EXPORT_DIRECTORY*>(
                      ImageDirectoryEntryToData(LoadedImage.MappedAddress,
                                                false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize)
               );
        if (ImageExportDirectory != nullptr) {
            dNameRVAs = static_cast<DWORD*>(ImageRvaToVa(LoadedImage.FileHeader,
                                                         LoadedImage.MappedAddress,
                                                         ImageExportDirectory->AddressOfNames, nullptr));
            for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++) {
                ret.emplace_back(static_cast<char*>(ImageRvaToVa(LoadedImage.FileHeader,
                                                                 LoadedImage.MappedAddress,
                                                                 dNameRVAs[i], nullptr)));
            }
        }
        UnMapAndLoad(&LoadedImage);
    }

    return ret;
}

bool libnm::IsSharedObject(std::string_view file) noexcept {
    return file.ends_with(".dll");
}
