//
// Created by tudom on 2020-01-08.
//

#pragma once

namespace info::dynamite {
  template<class R>
  using FixedReturnAbstractFunction = R (*)(...);

  using AbstractFunction = void (*)(...);

  using ConstAbstractFunction = void (* const)(...);
}
