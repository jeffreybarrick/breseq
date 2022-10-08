#=GENOME_DIFF	1.0
#=COMMAND	./src/c/breseq/breseq -j 4 -b 0 -o tests/lambda_short_sequence_repeats -r tests/lambda_short_sequence_repeats/../data/lambda/lambda.5.gbk tests/lambda_short_sequence_repeats/../data/lambda/lambda.short_sequence_repeats.fastq
#=REFSEQ	tests/lambda_short_sequence_repeats/../data/lambda/lambda.5.gbk
#=READSEQ	tests/lambda_short_sequence_repeats/../data/lambda/lambda.short_sequence_repeats.fastq
#=CONVERTED-BASES	250000
#=CONVERTED-READS	5000
#=INPUT-BASES	250000
#=INPUT-READS	5000
#=MAPPED-BASES	243455
#=MAPPED-READS	4884
INS	1	7	NC_001416-4	2604	GCGGCGGCG	gene_name=NinC	gene_position=coding (325/873 nt)	gene_product=NinC protein	gene_strand=>	genes_inactivated=NinC	locus_tag=lambdap64	locus_tags_inactivated=lambdap64	mutation_category=small_indel	position_end=2604	position_start=2604	ref_seq=G	repeat_length=3	repeat_new_copies=5	repeat_ref_copies=2	repeat_seq=GCG
DEL	2	8	NC_001416-4	2800	3	gene_name=NinC	gene_position=coding (521-523/873 nt)	gene_product=NinC protein	gene_strand=>	genes_inactivated=NinC	locus_tag=lambdap64	locus_tags_inactivated=lambdap64	mutation_category=small_indel	position_end=2802	position_start=2800	ref_seq=AAC	repeat_length=3	repeat_new_copies=1	repeat_ref_copies=2	repeat_seq=AAC
INS	3	9	NC_001416-4	2915	TTTT	gene_name=NinC	gene_position=coding (636/873 nt)	gene_product=NinC protein	gene_strand=>	genes_inactivated=NinC	locus_tag=lambdap64	locus_tags_inactivated=lambdap64	mutation_category=small_indel	position_end=2915	position_start=2915	ref_seq=T	repeat_length=1	repeat_new_copies=9	repeat_ref_copies=5	repeat_seq=T
DEL	4	10	NC_001416-4	5274	4	gene_name=Q	gene_position=coding (190-193/624 nt)	gene_product=late gene regulator	gene_strand=>	genes_inactivated=Q	locus_tag=lambdap71	locus_tags_inactivated=lambdap71	mutation_category=small_indel	position_end=5277	position_start=5274	ref_seq=CAAA	repeat_length=4	repeat_new_copies=1	repeat_ref_copies=2	repeat_seq=CAAA
MC	5	.	NC_001416-4	1	9	0	0	gene_name=–/P	gene_position=intergenic (–/-772)	gene_product=–/DNA replication protein	gene_strand=–/>	left_inside_cov=0	left_outside_cov=NA	locus_tag=–/lambdap61	right_inside_cov=10	right_outside_cov=13
MC	6	.	NC_001416-4	9674	9701	0	0	gene_name=lambdap79/–	gene_position=intergenic (+531/–)	gene_product=hypothetical protein/–	gene_strand=>/–	left_inside_cov=10	left_outside_cov=12	locus_tag=lambdap79/–	right_inside_cov=0	right_outside_cov=NA
JC	7	.	NC_001416-4	2597	1	NC_001416-4	2604	-1	-1	alignment_overlap=-1	coverage_minus=5	coverage_plus=18	flanking_left=50	flanking_right=50	frequency=1	junction_possible_overlap_registers=48	key=NC_001416-4__2597__1__NC_001416-4__2604__-1__-1__C__50__50__0__0	max_left=44	max_left_minus=38	max_left_plus=44	max_min_left=24	max_min_left_minus=23	max_min_left_plus=24	max_min_right=23	max_min_right_minus=11	max_min_right_plus=23	max_pos_hash_score=96	max_right=47	max_right_minus=34	max_right_plus=47	neg_log10_pos_hash_p_value=0.2	new_junction_coverage=1.10	new_junction_read_count=27	polymorphism_frequency=9.168e-01	pos_hash_score=21	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.04	side_1_gene_name=NinC	side_1_gene_position=coding (318/873 nt)	side_1_gene_product=NinC protein	side_1_gene_strand=>	side_1_locus_tag=lambdap64	side_1_overlap=0	side_1_possible_overlap_registers=49	side_1_read_count=1	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.16	side_2_gene_name=NinC	side_2_gene_position=coding (325/873 nt)	side_2_gene_product=NinC protein	side_2_gene_strand=>	side_2_locus_tag=lambdap64	side_2_overlap=0	side_2_possible_overlap_registers=49	side_2_read_count=4	side_2_redundant=0	total_non_overlap_reads=23	unique_read_sequence=C
JC	8	.	NC_001416-4	2799	-1	NC_001416-4	2803	1	0	alignment_overlap=4	coverage_minus=14	coverage_plus=8	flanking_left=50	flanking_right=50	frequency=1	junction_possible_overlap_registers=45	key=NC_001416-4__2799__-1__NC_001416-4__2799__1__4____50__50__0__0	max_left=42	max_left_minus=42	max_left_plus=38	max_min_left=22	max_min_left_minus=20	max_min_left_plus=22	max_min_right=20	max_min_right_minus=12	max_min_right_plus=20	max_pos_hash_score=90	max_right=44	max_right_minus=44	max_right_plus=37	neg_log10_pos_hash_p_value=0.3	new_junction_coverage=1.00	new_junction_read_count=23	polymorphism_frequency=9.616e-01	pos_hash_score=19	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.08	side_1_gene_name=NinC	side_1_gene_position=coding (520/873 nt)	side_1_gene_product=NinC protein	side_1_gene_strand=>	side_1_locus_tag=lambdap64	side_1_overlap=4	side_1_possible_overlap_registers=49	side_1_read_count=2	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=NinC	side_2_gene_position=coding (524/873 nt)	side_2_gene_product=NinC protein	side_2_gene_strand=>	side_2_locus_tag=lambdap64	side_2_overlap=0	side_2_possible_overlap_registers=45	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=22
JC	9	.	NC_001416-4	2911	1	NC_001416-4	2914	-1	0	alignment_overlap=1	coverage_minus=11	coverage_plus=11	flanking_left=50	flanking_right=50	frequency=1	junction_possible_overlap_registers=48	key=NC_001416-4__2911__1__NC_001416-4__2915__-1__1____50__50__0__0	max_left=48	max_left_minus=39	max_left_plus=48	max_min_left=21	max_min_left_minus=21	max_min_left_plus=18	max_min_right=23	max_min_right_minus=23	max_min_right_plus=23	max_pos_hash_score=96	max_right=46	max_right_minus=34	max_right_plus=46	neg_log10_pos_hash_p_value=0.2	new_junction_coverage=1.06	new_junction_read_count=26	polymorphism_frequency=8.539e-01	pos_hash_score=21	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.20	side_1_gene_name=NinC	side_1_gene_position=coding (632/873 nt)	side_1_gene_product=NinC protein	side_1_gene_strand=>	side_1_locus_tag=lambdap64	side_1_overlap=1	side_1_possible_overlap_registers=49	side_1_read_count=5	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.16	side_2_gene_name=NinC	side_2_gene_position=coding (635/873 nt)	side_2_gene_product=NinC protein	side_2_gene_strand=>	side_2_locus_tag=lambdap64	side_2_overlap=0	side_2_possible_overlap_registers=48	side_2_read_count=4	side_2_redundant=0	total_non_overlap_reads=22
JC	10	.	NC_001416-4	5273	-1	NC_001416-4	5278	1	0	alignment_overlap=5	coverage_minus=19	coverage_plus=5	flanking_left=50	flanking_right=50	frequency=1	junction_possible_overlap_registers=44	key=NC_001416-4__5273__-1__NC_001416-4__5273__1__5____50__50__0__0	max_left=44	max_left_minus=43	max_left_plus=44	max_min_left=21	max_min_left_minus=21	max_min_left_plus=18	max_min_right=22	max_min_right_minus=22	max_min_right_plus=12	max_pos_hash_score=88	max_right=43	max_right_minus=43	max_right_plus=27	neg_log10_pos_hash_p_value=0.2	new_junction_coverage=1.11	new_junction_read_count=25	polymorphism_frequency=1.000e+00	pos_hash_score=20	prediction=consensus	side_1_annotate_key=gene	side_1_continuation=0	side_1_coverage=0.00	side_1_gene_name=Q	side_1_gene_position=coding (189/624 nt)	side_1_gene_product=late gene regulator	side_1_gene_strand=>	side_1_locus_tag=lambdap71	side_1_overlap=5	side_1_possible_overlap_registers=49	side_1_read_count=0	side_1_redundant=0	side_2_annotate_key=gene	side_2_continuation=0	side_2_coverage=0.00	side_2_gene_name=Q	side_2_gene_position=coding (194/624 nt)	side_2_gene_product=late gene regulator	side_2_gene_strand=>	side_2_locus_tag=lambdap71	side_2_overlap=0	side_2_possible_overlap_registers=44	side_2_read_count=0	side_2_redundant=0	total_non_overlap_reads=24
UN	11	.	NC_001416-4	1	6
UN	12	.	NC_001416-4	2800	2802
UN	13	.	NC_001416-4	5274	5277
UN	14	.	NC_001416-4	9687	9701
