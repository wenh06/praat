/* KlattGrid_def.h
 *
 * Copyright (C) 2008-2011 David Weenink, 2015 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define ooSTRUCT PhonationPoint
oo_DEFINE_CLASS (PhonationPoint, AnyPoint)

	oo_DOUBLE (period)   // 1/F0
	oo_DOUBLE (openPhase)
	oo_DOUBLE (collisionPhase)
	oo_DOUBLE (te)   // time from glottis open to exponential decay or closing
	oo_DOUBLE (power1)   // flow function
	oo_DOUBLE (power2)
	oo_DOUBLE (pulseScale)   // multiplier for diplophonia, shimmer

oo_END_CLASS (PhonationPoint)
#undef ooSTRUCT


#define ooSTRUCT PhonationTier
oo_DEFINE_CLASS (PhonationTier, Function)

	oo_COLLECTION_OF (SortedSetOfDoubleOf, points, PhonationPoint, 0)

	#if oo_DECLARING
		AnyTier_METHODS
	#endif

oo_END_CLASS (PhonationTier)
#undef ooSTRUCT


#define ooSTRUCT PhonationGridPlayOptions
oo_DEFINE_CLASS (PhonationGridPlayOptions, Daata)

	oo_INT (voicing)
	oo_INT (aspiration)
	oo_INT (breathiness)
	oo_INT (flutter)
	oo_INT (doublePulsing)
	oo_INT (collisionPhase)
	oo_INT (spectralTilt)
	oo_INT (flowFunction)   // 1: user-defined with tiers (power1, power2); 2: (2,3); 3: (3,4)
	oo_INT (flowDerivative)
	oo_DOUBLE (maximumPeriod)

oo_END_CLASS (PhonationGridPlayOptions)
#undef ooSTRUCT


#define ooSTRUCT PhonationGrid
oo_DEFINE_CLASS (PhonationGrid, Function)

	oo_AUTO_OBJECT (PitchTier, 0, pitch)
	oo_AUTO_OBJECT (RealTier, 0, flutter) // [0,1]
	oo_AUTO_OBJECT (IntensityTier, 0, voicingAmplitude) // dB
	oo_AUTO_OBJECT (RealTier, 0, doublePulsing) // [0,1]
	oo_AUTO_OBJECT (RealTier, 0, openPhase) // (0,1)
	oo_AUTO_OBJECT (RealTier, 0, collisionPhase) //
	oo_AUTO_OBJECT (RealTier, 0, power1) // 2,3..
	oo_AUTO_OBJECT (RealTier, 0, power2) // 3,4.. power2>power1
	oo_AUTO_OBJECT (IntensityTier, 0, spectralTilt) // dB
	oo_AUTO_OBJECT (IntensityTier, 0, aspirationAmplitude) // dB
	oo_AUTO_OBJECT (IntensityTier, 0, breathinessAmplitude) // dB
	#if !oo_READING && !oo_WRITING
		oo_AUTO_OBJECT (PhonationGridPlayOptions, 0, options)
	#endif
	#if oo_READING
		options = PhonationGridPlayOptions_create ();
		PhonationGrid_setNames (this);
	#endif
	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (PhonationGrid)
#undef ooSTRUCT


#define ooSTRUCT VocalTractGridPlayOptions
oo_DEFINE_CLASS (VocalTractGridPlayOptions, Daata)

	oo_INT (filterModel)
	oo_LONG (startOralFormant)
	oo_LONG (endOralFormant)
	oo_LONG (startNasalFormant)
	oo_LONG (endNasalFormant)
	oo_LONG (startNasalAntiFormant)
	oo_LONG (endNasalAntiFormant)

oo_END_CLASS (VocalTractGridPlayOptions)
#undef ooSTRUCT


#define ooSTRUCT VocalTractGrid
oo_DEFINE_CLASS (VocalTractGrid, Function)

	oo_AUTO_OBJECT (FormantGrid, 0, oral_formants)
	oo_AUTO_OBJECT (FormantGrid, 0, nasal_formants)
	oo_AUTO_OBJECT (FormantGrid, 0, nasal_antiformants)
	// for parallel synthesis
	oo_COLLECTION_OF (OrderedOf, oral_formants_amplitudes, IntensityTier, 0)
	oo_COLLECTION_OF (OrderedOf, nasal_formants_amplitudes, IntensityTier, 0)

	#if !oo_READING && !oo_WRITING
		oo_AUTO_OBJECT (VocalTractGridPlayOptions, 0, options)
	#endif

	#if oo_READING
		options = VocalTractGridPlayOptions_create ();
		VocalTractGrid_setNames (this);
	#endif

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (VocalTractGrid)
#undef ooSTRUCT


#define ooSTRUCT CouplingGridPlayOptions
oo_DEFINE_CLASS (CouplingGridPlayOptions, Daata)

	oo_LONG (startTrachealFormant)
	oo_LONG (endTrachealFormant)
	oo_LONG (startTrachealAntiFormant)
	oo_LONG (endTrachealAntiFormant)
	oo_LONG (startDeltaFormant)
	oo_LONG (endDeltaFormant)
	oo_LONG (startDeltaBandwidth)
	oo_LONG (endDeltaBandwidth)
	oo_INT (openglottis)
	oo_DOUBLE (fadeFraction)

oo_END_CLASS (CouplingGridPlayOptions)
#undef ooSTRUCT


#define ooSTRUCT CouplingGrid
oo_DEFINE_CLASS (CouplingGrid, Function)

	oo_AUTO_OBJECT (FormantGrid, 0, tracheal_formants)
	oo_AUTO_OBJECT (FormantGrid, 0, tracheal_antiformants)
	oo_COLLECTION_OF (OrderedOf, tracheal_formants_amplitudes, IntensityTier, 0)
	oo_AUTO_OBJECT (FormantGrid, 0, delta_formants)

	#if !oo_READING && !oo_WRITING
		oo_AUTO_OBJECT (PhonationTier, 0, glottis)
		oo_AUTO_OBJECT (CouplingGridPlayOptions, 0, options)
	#endif

	#if oo_READING
		options = CouplingGridPlayOptions_create ();
		glottis = PhonationTier_create (xmin, xmax);
		CouplingGrid_setNames (this);
	#endif

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (CouplingGrid)
#undef ooSTRUCT


#define ooSTRUCT FricationGridPlayOptions
oo_DEFINE_CLASS (FricationGridPlayOptions, Daata)

	oo_LONG (startFricationFormant)
	oo_LONG (endFricationFormant)
	oo_INT (bypass)

oo_END_CLASS (FricationGridPlayOptions)
#undef ooSTRUCT


#define ooSTRUCT FricationGrid
oo_DEFINE_CLASS (FricationGrid, Function)

	oo_AUTO_OBJECT (IntensityTier, 0, fricationAmplitude) // dB
	oo_AUTO_OBJECT (FormantGrid, 0, frication_formants)
	oo_COLLECTION_OF (OrderedOf, frication_formants_amplitudes, IntensityTier, 0)
	oo_AUTO_OBJECT (IntensityTier, 0, bypass) // dB

	#if !oo_READING && !oo_WRITING
		oo_AUTO_OBJECT (FricationGridPlayOptions, 0, options)
	#endif

	#if oo_READING
		options = FricationGridPlayOptions_create ();
		FricationGrid_setNames (this);
	#endif

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (FricationGrid)
#undef ooSTRUCT


#define ooSTRUCT KlattGridPlayOptions
oo_DEFINE_CLASS (KlattGridPlayOptions, Daata)

	oo_DOUBLE (samplingFrequency)
	oo_INT (scalePeak)
	oo_DOUBLE (xmin)
	oo_DOUBLE (xmax)

oo_END_CLASS (KlattGridPlayOptions)
#undef ooSTRUCT


#define ooSTRUCT KlattGrid
oo_DEFINE_CLASS (KlattGrid, Function)

	oo_AUTO_OBJECT (PhonationGrid, 0, phonation)   // glottal source
	oo_AUTO_OBJECT (VocalTractGrid, 0, vocalTract) // filter
	oo_AUTO_OBJECT (CouplingGrid, 0, coupling)     // coupling between source and filter
	oo_AUTO_OBJECT (FricationGrid, 0, frication)   // frication source
	oo_AUTO_OBJECT (IntensityTier, 0, gain)        // final scaling

	#if !oo_READING && !oo_WRITING
		oo_AUTO_OBJECT (KlattGridPlayOptions, 0, options)
	#endif

	#if oo_READING
		options = KlattGridPlayOptions_create ();
		KlattGrid_setNames (this);
	#endif

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (KlattGrid)
#undef ooSTRUCT

/* End of file KlattGrid_def.h */
