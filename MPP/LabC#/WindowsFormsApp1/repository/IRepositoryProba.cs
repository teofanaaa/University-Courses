﻿using Concurs.model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Concurs.repository
{
    public interface IRepositoryProba: IRepository<int, Proba>
    {
        IEnumerable<string> ListaCategorii();
        IEnumerable<string> ListaProbeNume();
    }
}
