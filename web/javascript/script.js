$(document).ready(function() {

	/* DROPDOWNS */
	$('.ui.dropdown').dropdown();
	$('.ui.selection.dropdown').dropdown();

	/* ACCORDION */
	$('.ui.accordion').accordion();

	/* TRANSITIONS */
	$('.ui.blue.button.show.form').click(function() {
		$('.form.thread').transition('slide down');
	});
	$('.ui.blue.tiny.button.show.comment').click(function() {
		$(this).parents('.post').children('.form.comment').transition('slide down');
	});
	$('.show.activities').click(function() {
		if ($(this).attr("class") == "show activities")
			$(this).attr("class", "show activities active");
		else
			$(this).attr("class", "show activities");
		if ($(this).parents('tbody').children(".hidden."+$(this).attr("data-text")).length != 0)
			$(this).parents('tbody').children(".hidden."+$(this).attr("data-text")).attr("class", ""+$(this).attr("data-text"));
		else
			$(this).parents('tbody').children("."+$(this).attr("data-text")).attr("class", "hidden "+$(this).attr("data-text"));
	});

	/* COPYBUTTON */
	$('.zclip').zclip({
		path:'/flash/zClip.swf',
		copy:$('.ui.content.hidden').text()
	});

	/* SORT */
	$('.ui.sortable').tablesort();

	/* RANGE */
	$('.directory_option').click(function(){
		$(location).attr('href', "./?range="+$(this).attr("data-text"));
	});

	/* POPUPS */
	$(".ui.tiny.icon.button").popup();
	$(".part").popup();

	/* KNOB */
	$(".donught.chart").knob({
		readOnly:true,
		fgColor:"#6ECFF5"
	});

	/* CALENDAR */
	var date = new Date();
	var d = date.getDate();
	var m = date.getMonth();
	var y = date.getFullYear();
	var href = $(location).attr('href');

	$("#calendarfr").fullCalendar({
		header: {
			left: 'title',
			center: '',
			right: 'month,agendaWeek,agendaDay, today, prev,next'
		},
		firstDay: 1,
		firstHour: 0,
		defaultView: 'agendaWeek',
		events: href.substr(0, href.length - 10) + '/profile/activitiesfeed',
		monthNames: ['Janvier', 'Février', 'Mars', 'Avril', 'Mai', 'Juin', 'Juillet', 'Août', 'Septembre', 'Novembre', 'Décembre'],
		monthNamesShort: ['Jan', 'Fév', 'Mar', 'Avr', 'Mai', 'Jui','Juil', 'Aoû', 'Sep', 'Oct', 'Nov', 'Déc'],
		dayNames: ['Dimanche', 'Lundi', 'Mardi', 'Mercredi', 'Jeudi', 'Vendredi', 'Samedi'],
		dayNamesShort: ['Dim', 'Lun', 'Mar', 'Mer', 'Jeu', 'Ven', 'Sam'],
		allDayText: 'Continu',
		timeFormat: 'HH:mm{ - H:mm}',
		axisFormat: 'HH:mm',
		buttonText: {
			today: "Aujourd'hui",
			month: 'MOIS',
			week: 'SEMAINE',
			day: 'JOUR'
		},
		columnFormat: {
			month: 'ddd',
			week: 'ddd d/M',
			day: 'dddd d/M'
		},
		titleFormat: {
			month: 'MMMM yyyy',
			week: "d[ MMM] [ yyyy]{ '&#8211;' d} {MMM} {yyyy}",
			day: 'dddd d MMM yyyy'
		}
	});

	$("#calendaren").fullCalendar({
		header: {
			left: 'title',
			center: '',
			right: 'month,agendaWeek,agendaDay, today, prev,next'
		},
		firstDay: 1,
		firstHour: 0,
		defaultView: 'agendaWeek',
		events: href.substr(0, href.length - 10) + '/profile/activitiesfeed',
		buttonText: {
			today: "Today",
			month: 'MONTH',
			week: 'WEEK',
			day: 'DAY'
		},
	});

	$(".elearning_menu").click(function (){
		var $i = $(this).attr("id");
		var $el = $('.elearning_content#' + $i);
		$('.elearning_content').hide();
		$el.show();
	});

	$('.ui.modal').modal('attach events', '.register-group', 'show');

	$('#site_activitybundle_activitygroup_name').keyup(function(event)
	{
		if ($(this).val() != "")
		{
			$('.error-group').hide();
			$('.validate-group').removeAttr("style");
			$('.validate-group').prop("disabled", false);
		}
	});

	$('.target-validate-group').click(function(){
		if ($('#site_activitybundle_activitygroup_name').val() == "")
		{
			$('.error-group').show();
		}
	});

	$('.search-bar').keypress(function (e){
		if (e.which == 13)
		{
			var href = $(location).attr('href');
			var n = href.indexOf('/', 10);
			var url = href.substr(0, n) + '/profile/';
			url = url + $(this).val();
			$.ajax({
				url: url,
				success: function (){
					window.location.href = url;
				},
				error: function (){
					$('.ui.small.icon.input').addClass('error');
				},
			});
		}
	});

});
